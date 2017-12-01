#ifndef QGLESWIDGET_H
#define QGLESWIDGET_H

#include <QWidget>
#include <FreeImage.h>
#include <QKeyEvent>
#include <QMouseEvent>
#include "tool/CELLMath.hpp"
#include "tool/program_p2_c4.h"
#include "tool/mycamera.h"
#define MESA_EGL_NO_X11_HEADERS
#include <EGL/egl.h>
#include <GLES2/gl2.h>

enum KEYMODE
{
    KEY_NULL,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_W,
};

enum MOUSEMODE
{
    MOUSE_NULL,
    MOUSE_LEFTDOWN,
    MOUSE_RIGHTDOWN,
    MOUSE_LEFTUP,
    MOUSE_RIGHTUP,
    MOUSE_WHEEL,
};

typedef struct
{
    float x,y,z;
    float nx,ny,nz;
    float u,v;
}Vertex;

typedef struct
{
    float x,y,z;
    float nx,ny,nz;
    float u,v;
}V3N3;

struct VertexPUV
{
    float x,y,z;
    float u,v;
    float u1,v1;
};

class QGLESWIDGET : public QWidget
{
    Q_OBJECT
public:
    explicit QGLESWIDGET(QWidget *parent = 0);
    ~QGLESWIDGET();

    //! 窗口的高度
    int         _width;
    //! 窗口的宽度
    int         _height;
    /// for gles2.0
    EGLConfig   _config;
    EGLSurface  _surface;
    EGLContext  _context;
    EGLDisplay  _display;

    //! 增加shader
    PROGRAM_P2_C4   _shader;
    MYCAMERA        _camera;
    unsigned int    _texMask;
    unsigned int    _texBrush1;
    unsigned int    _texBrush2;
    unsigned int    _texBrush3;
    unsigned int    _texBrush4;

    unsigned int loadTexture(const char *fileName);

    CELL::Rgba _color[4];
    int _brush;
    void updataMask(int x, int y, CELL::Rgba color);

    bool init_QGW(std::vector<QString> fileName);

    //! 初始化 OpenGLES2.0
    bool    initOpenGLES20();
    //! 销毁OpenGLES2.0
    void    destroyOpenGLES20();

    virtual void render();
    void drawImage();


    QObject *parent;
    //!实现键盘事件
    bool eventFilter( QObject * target , QEvent * event );
    void keyPressEvent(QKeyEvent * e);

    //!鼠标事件
    CELL::float2 pos;
    MOUSEMODE typeMouse;
    bool leftB;
    bool rightB;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

signals:
    void sendKeyEvent(KEYMODE key);
    void sendMouseEvent(MOUSEMODE mouse,CELL::int2 pstart,CELL::int2 pend);
    void sendWheelEvent(MOUSEMODE mouse,int p,CELL::int2 pos);
public slots:
};

#endif // QGLESWIDGET_H
