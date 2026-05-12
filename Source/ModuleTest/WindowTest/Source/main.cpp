#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

int main(int argc, char **argv) {
    // 创建一个窗口，位置(100,100)，大小(400,300)
    Fl_Window *window = new Fl_Window(400, 300, "Hello World");

    // 创建一个文本显示框，位置(0,0)，宽度400，高度200
    // FL_ALIGN_WRAP | FL_ALIGN_INSIDE 表示文字自动换行并居中
    Fl_Box *box = new Fl_Box(0, 0, 400, 200, "Hello, World!");
    box->box(FL_FLAT_BOX);           // 设置边框样式
    box->labelsize(36);              // 字体大小
    box->labelfont(FL_BOLD);         // 粗体
    box->labelcolor(FL_BLUE);        // 文字颜色

    // 结束窗口的添加操作
    window->end();

    // 显示窗口
    window->show(argc, argv);

    // 进入 FLTK 事件循环
    return Fl::run();
}