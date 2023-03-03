#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QColorDialog>
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RecountColors(const RGB& rgb) {
 rgb_ = rgb;
 xyz_ = XYZ(rgb);
 cmyk_ = CMYK(rgb);
}

void MainWindow::RecountColors(const XYZ& xyz) {
 rgb_ = RGB(xyz);
 xyz_ = xyz;
 cmyk_ = CMYK(xyz);
}

void MainWindow::RecountColors(const CMYK& cmyk) {
 rgb_ = RGB(cmyk);
 xyz_ = XYZ(cmyk);
 cmyk_ = cmyk;
}


void MainWindow::RenewValues()
{
    from_prog = true;
    ui->R->setValue(rgb_.red);
    ui->G->setValue(rgb_.green);
    ui->B->setValue(rgb_.blue);
    rgb_.red = ui->R->value();
    rgb_.green = ui->G->value();
    rgb_.blue = ui->B->value();

    ui->X->setValue(xyz_.x);
    ui->XYZY->setValue(xyz_.y);
    ui->Z->setValue(xyz_.z);

    ui->C->setValue(cmyk_.cyan);
    ui->M->setValue(cmyk_.magenta);
    ui->Y->setValue(cmyk_.yellow);
    ui->K->setValue(cmyk_.k);
    qDebug() << rgb_.red << " " << rgb_.green << " " <<  rgb_.blue << "\n";
    SetColor(QColor::fromRgb(rgb_.red, rgb_.green, rgb_.blue));
    from_prog = false;
}

void MainWindow::SetColor(QColor clr)
{
    QPalette p = ui->label->palette();
    p.setColor(ui->label->backgroundRole(), clr);
    ui->label->setAutoFillBackground(true);
    ui->label->setPalette(p);
}



void MainWindow::on_chooseButton_clicked()
{
    QColor clr = QColorDialog::getColor();
    clr.getRgb(&rgb_.red, &rgb_.green, &rgb_.blue);
    RecountColors(rgb_);

    RenewValues();
}


void MainWindow::on_R_textChanged()
{
    if (from_prog) {
        return;
    }
    try{
    rgb_.red = ui->R->value();
    } catch (std::invalid_argument& arg) {
        return;
    }
    RecountColors(rgb_);
    RenewValues();
}


void MainWindow::on_G_textChanged()
{
    if (from_prog) {
        return;
    }
    try{
    rgb_.green = ui->G->value();
} catch (std::invalid_argument& arg) {
    return;
}
    RecountColors(rgb_);
    RenewValues();
}


void MainWindow::on_B_textChanged()
{
    if (from_prog) {
        return;
    }
    try{
    rgb_.blue = ui->B->value();
} catch (std::invalid_argument& arg) {
    return;
}
    RecountColors(rgb_);
    RenewValues();
}


void MainWindow::on_C_textChanged()
{
    if (from_prog) {
        return;
    }
    try{
    cmyk_.cyan =ui->C->value();
} catch (std::invalid_argument& arg) {
    return;
}
    RecountColors(cmyk_);
    RenewValues();
}


void MainWindow::on_M_textChanged()
{
    if (from_prog) {
        return;
    }
    try{
    cmyk_.magenta = ui->M->value();
} catch (std::invalid_argument& arg) {
    return;
}
    RecountColors(cmyk_);
    RenewValues();
}


void MainWindow::on_Y_textChanged()
{
    if (from_prog) {
        return;
    }
    try{
    cmyk_.yellow = ui->Y->value();
} catch (std::invalid_argument& arg) {
    return;
}
    RecountColors(cmyk_);
    RenewValues();
}


void MainWindow::on_K_textChanged()
{
    if (from_prog) {
        return;
    }
    try{
    cmyk_.k = ui->K->value();
} catch (std::invalid_argument& arg) {
    return;
}
    RecountColors(cmyk_);
    RenewValues();
}


void MainWindow::on_X_textChanged()
{
    if (from_prog) {
        return;
    }
    try{
    xyz_.x = ui->X->value();
} catch (std::invalid_argument& arg) {
    return;
}
    RecountColors(xyz_);
    RenewValues();
}


void MainWindow::on_XYZY_textChanged()
{
    if (from_prog) {
        return;
    }
    try{
    xyz_.y = ui->XYZY->value();
} catch (std::invalid_argument& arg) {
    return;
}
    RecountColors(xyz_);
    RenewValues();

}


void MainWindow::on_Z_textChanged()
{
    if (from_prog) {
        return;
    }
    try{
    xyz_.z = ui->Z->value();
} catch (std::invalid_argument& arg) {
    return;
}
    RecountColors(xyz_);
    RenewValues();
}


void MainWindow::on_R_editingFinished()
{
        if (from_prog) {
            return;
        }
        try{
        rgb_.red = ui->R->value();
        } catch (std::invalid_argument& arg) {
            return;
        }
        RecountColors(rgb_);
        RenewValues();
}


void MainWindow::on_G_editingFinished()
{
    if (from_prog) {
        return;
    }
    try{
    rgb_.green = ui->G->value();
    } catch (std::invalid_argument& arg) {
        return;
    }
    RecountColors(rgb_);
    RenewValues();
}


void MainWindow::on_B_editingFinished()
{
    if (from_prog) {
        return;
    }
    try{
    rgb_.blue = ui->B->value();
    } catch (std::invalid_argument& arg) {
        return;
    }
    RecountColors(rgb_);
    RenewValues();
}

