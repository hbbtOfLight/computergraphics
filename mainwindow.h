#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "color_structs.h"

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
    void on_chooseButton_clicked();

    void on_R_textChanged();

    void on_G_textChanged();

    void on_B_textChanged();

    void on_C_textChanged();

    void on_M_textChanged();

    void on_Y_textChanged();

    void on_K_textChanged();

    void on_X_textChanged();

    void on_XYZY_textChanged();

    void on_Z_textChanged();

    void on_R_editingFinished();

    void on_G_editingFinished();

    void on_B_editingFinished();

private:
    void RecountColors(const RGB& rgb);
    void RecountColors(const XYZ& xyz);
    void RecountColors(const CMYK& cmyk);
    void RenewValues();
    void SetColor(QColor clr);
    bool from_prog = false;
    RGB rgb_;
    XYZ xyz_;
    CMYK cmyk_;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
