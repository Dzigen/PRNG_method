#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QDate>
#include <QtMath>
#include <QFile>
#include "parametres.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    /**
     * @brief generate_parameters Генерируем параметры для линейного конгруэнтного
     * генератора
     */
    void generate_parameters();

    /**
     * @brief generate_sequence генерируем последовательность ПСЧ
     * @param len длина генерируемой последовательности
     */
    void generate_sequence(long len);


    void on_buttonGenerateSeq_released();


    void on_buttonGenerateParams_released();

    /**
     * @brief on_buttonViewDiagram_released Выводим окно с гистограмой
     * распределения частот сгенерированной последовательности ПСЧ
     */
    void on_buttonViewDiagram_released();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
