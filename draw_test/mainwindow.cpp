#include "mainwindow.h"
#include <ui_mainwindow.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    DrawManager::set_data_map({
        { DrawManager::NON_WALKABLE, QPixmap(":/sprites/Resources/sprites/nonwalk.png") },
        { DrawManager::WALKABLE,     QPixmap(":/sprites/Resources/sprites/walk.png")    },
        { DrawManager::USER1,        QPixmap(":/sprites/Resources/sprites/user1.png")   },
        { DrawManager::USER2,        QPixmap(":/sprites/Resources/sprites/user2.png")   },
        { DrawManager::USER3,        QPixmap(":/sprites/Resources/sprites/user3.png")   },
    });

    int font_id = QFontDatabase::addApplicationFont(":/fonts/Resources/font/RobotoMono-VariableFont_wght.ttf");
    QString font_family = QFontDatabase::applicationFontFamilies(font_id).at(0);
    QFont f(font_family);
    ui->pte_mapinput->setFont(f);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ui_lock(bool to_lock) {
    ui->btn_parsemap->setEnabled(!to_lock);
    ui->pte_mapinput->setEnabled(!to_lock);
    ui->gv_field->setEnabled(!to_lock);
}


void MainWindow::on_btn_parsemap_clicked() {
    this->ui_lock(true);

    auto s = ui->pte_mapinput->toPlainText();
    DrawManager::map_type n_map;

    setStatusTip("Parsing...");
    auto rows = s.split("\n");

    int posX = 0, posY = 0;
    for (auto row : rows) {
        if (row.length() > 25) {
            setStatusTip("Too long row, will be truncated to 25");
        }
        for (char c : row.toStdString()) {
            n_map.push_back({QPoint(posX * DrawManager::SPRITE_SIZE, posY * DrawManager::SPRITE_SIZE), DrawManager::get_type_by_char(c)});
            posX += 1;
        }
        posX = 0;
        posY += 1;
    }

    setStatusTip("Drawing...");
    ui->gv_field->set_map(n_map);
    ui->gv_field->update();

    setStatusTip("Done.");

    this->ui_lock(false);
}

void MainWindow::on_action_5_triggered()
{
    QApplication::quit();
}

void MainWindow::on_action_10_triggered()
{
    QMessageBox::information(this, "справка",
                             "На поле 25*25 позиций распложены препятствия и атомы молекулы,"
                             " представленном на изображении справа. Необходимо собрать молекулу на поле слева,"
                             " при этом атомы могут перемещаться только по горизонтали и вертикали и менять "
                             "направление движения только в определенных местах.");
}

void MainWindow::on_action_12_triggered()
{
    window = new okno(this);
    window->show();

    QMessageBox::information(this, "таблица рекордов", "1. AAA        100500 \n"
                                                       "2. bbb          2332\n"
                                                       "3. ccc          1132\n"
                                                       "4. ddd          1000\n"
                                                       "5. fefe          999\n"
                                                       "6. cds           888\n"
                                                       "7. cdcd          777\n"
                                                       "8. cdecc         666\n"
                                                       "9. de            555\n"
                                                      "10. eada          444\n");
}


