#include "program_p2_c4.h"

PROGRAM_P2_C4::PROGRAM_P2_C4()
{
    _position       =   -1;
    _uv             =   -1;
    _uv1            =   -1;
    _MVP            =   -1;
    _texMask        =   -1;
    _texBrush1      =   -1;
    _texBrush2      =   -1;
    _texBrush3      =   -1;
    _texBrush4      =   -1;
}

bool PROGRAM_P2_C4::initialize()
{
#if 0
    //!使用1个模板文理和1个刷绘文理进行刷绘,使用参数和相对应的shader程序
    //! 参数1、attribute   _position;
    //! 参数2、attribute   _uv;
    //! 参数3、uniform     _MVP;
    //! 参数4、uniform     _texBrush;
    //! 参数5、uniform     _texMask;
    const char* vs  =
    {
        "uniform    mat4    _MVP;"
        "attribute  vec3    _position;"
        "attribute  vec2    _uv;"
        "varying    vec2    _outUV;"
        "void main()"
        "{"
        "   _outUV      =   _uv;"
        "   gl_Position =   _MVP * vec4(_position,1.0);"
        "}"
    };

    const char* ps  =
    {
        "precision  lowp    float; "
        "uniform    sampler2D   _texMask;"
        "uniform    sampler2D   _texBrush;"
        "varying    vec2        _outUV;"
        "void main()"
        "{"
        "   vec4 color0  =   texture2D(_texMask,_outUV);"
        "   vec4 color1  =   texture2D(_texBrush,_outUV);"
        "   gl_FragColor =   color0.r * color1;"
        "}"
    };
#elif 1
    //!注意1：这里使用了两套uv，一个uv是模板的，一个uv1是刷绘文理的。
    //! uv1的迭代要视情况调整，一般比uv大，可以清晰的看到刷绘文理的纹路。
    //!注意2：这里把通道a的颜色去掉了，是因为使用的图像没有a通道，
    //! 如果使用，会使背景有文理而其它的文理都变成混合的白色。
    const char* vs  =
    {
        "uniform    mat4    _MVP;"
        "attribute  vec3    _position;"
        "attribute  vec2    _uv;"
        "attribute  vec2    _uv1;"
        "varying    vec2    _outUV;"
        "varying    vec2    _outUV1;"
        "void main()"
        "{"
        "   _outUV      =   _uv;"
        "   _outUV1     =   _uv1;"
        "   gl_Position =   _MVP * vec4(_position,1.0);"
        "}"
    };
    const char* ps  =
    {
        "precision  lowp    float; "
        "uniform    sampler2D   _texMask;"
        "uniform    sampler2D   _texBrush1;"
        "uniform    sampler2D   _texBrush2;"
        "uniform    sampler2D   _texBrush3;"
        "uniform    sampler2D   _texBrush4;"
        "varying    vec2        _outUV;"
        "varying    vec2        _outUV1;"
        "void main()"
        "{"
        "   vec4 color0  =   texture2D(_texMask,_outUV);"
        "   vec4 color1  =   texture2D(_texBrush1,_outUV1);"
        "   vec4 color2  =   texture2D(_texBrush2,_outUV1);"
        "   vec4 color3  =   texture2D(_texBrush3,_outUV1);"
        "   vec4 color4  =   texture2D(_texBrush4,_outUV1);"
        "   vec4 color   =   color0.r * color1;"
        "        color   +=  color0.g * color2;"
        "        color   +=  color0.b * color3;"
//        "        color   +=  color0.a * color4;"
        "   gl_FragColor =   color;"
        "}"
    };
#else
#endif
    bool    res =   createProgram(vs,ps);
    if(res)
    {
        _position   =   glGetAttribLocation(_programId,"_position");
        _uv         =   glGetAttribLocation(_programId,"_uv");
        _uv1        =   glGetAttribLocation(_programId,"_uv1");
        _MVP        =   glGetUniformLocation(_programId,"_MVP");
        _texMask    =   glGetUniformLocation(_programId,"_texMask");
        _texBrush1  =   glGetUniformLocation(_programId,"_texBrush1");
        _texBrush2  =   glGetUniformLocation(_programId,"_texBrush2");
        _texBrush3  =   glGetUniformLocation(_programId,"_texBrush3");
        _texBrush4  =   glGetUniformLocation(_programId,"_texBrush4");
    }
    return  res;
}

void PROGRAM_P2_C4::begin()
{
    glUseProgram(_programId);
    //!在显卡里面使用的局部变量，在使用时是需要进行使能和关闭的
    glEnableVertexAttribArray(_position);       
    glEnableVertexAttribArray(_uv);
    glEnableVertexAttribArray(_uv1);
}

void PROGRAM_P2_C4::end()
{
    glDisableVertexAttribArray(_position);
    glDisableVertexAttribArray(_uv);
    glDisableVertexAttribArray(_uv1);
    glUseProgram(0);
}
