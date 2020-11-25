#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QDialog>
#include "parametres.h"

namespace Ui {
class Diagram;
}

class Diagram : public QDialog
{
    Q_OBJECT

public:
    explicit Diagram(QWidget *parent = nullptr);
    ~Diagram();

    /**
     * @brief draw_diagram Отрисовываем гистограмму распределения ПСЧ
     * по интервалам возможных чначений
     */
    void draw_diagram();

    /**
     * @brief get_min_man_max_distribution Вычисление максимальной,
     * относитеьной и минимальной относительных частот попадания сгенерированных
     * значений в каждый из интервалов
     *
     * @param distribution относительное распределение ПСЧ
     * по соответствующим интервалам
     */
    void get_min_man_max_distribution(QVector<double> distribution);

    /**
     * @brief get_distribution вычисляем относительное распределение
     * сгенерированных ПСЧ по интервалам (в процентах)
     * @return  вектор относительных частот
     */
    QVector<double> get_distribution();

private:
    Ui::Diagram *ui;
};

#endif // DIAGRAM_H
