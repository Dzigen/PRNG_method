#ifndef DIAGRAMWINDOW_H
#define DIAGRAMWINDOW_H

#include <QMainWindow>

namespace Ui {
class DiagramWindow;
}

class DiagramWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DiagramWindow(QWidget *parent = nullptr);
    ~DiagramWindow();

private:
    Ui::DiagramWindow *ui;
};

#endif // DIAGRAMWINDOW_H
