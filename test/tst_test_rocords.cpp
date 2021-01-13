#include <QtTest>
#include "../draw_test/rocords.h"
#include "../draw_test/extendedgraphicview.h"
#include "../draw_test/drawmanager.h"

// add necessary includes here

class test_rocords : public QObject
{
    Q_OBJECT

public:
    test_rocords();
    ~test_rocords();
    ExtendedGraphicView *H;

private slots:
    void test_rocords_case_NN();
    void test_rocords_case_LL();
    void test_rocords_case_SS();
    void test_rocords_case_probel();

    void test_graphics_case_1();
    void test_graphics_case_2();
    void test_graphics_case_3();
//    void test_graphics_case_4();
//    void test_graphics_case_5();


};

test_rocords::test_rocords()
{
    H = new ExtendedGraphicView();
    DrawManager::map_type n_map;

    QString s = "t \n"
                "  ";
    auto rows = s.split("\n");

    int posX = 0, posY = 0;
    for (auto row : rows) {
        for (char c : row.toStdString()) {
            n_map.push_back({QPoint(posX, posY), DrawManager::get_type_by_char(c)});
            posX += 1;
        }
        posX = 0;
        posY += 1;
    }

    H->set_map(n_map);
}

test_rocords::~test_rocords()
{

}

void test_rocords::test_rocords_case_NN(){
  auto name="Testing";
  rocords s(name,2,2);
  QVERIFY2(
        s.NN()==name, "ошибка имени"
        );
}
void test_rocords::test_rocords_case_LL(){
  auto l = 3;
  rocords s("gocha",l,2);
   QVERIFY2(
         s.LL()==l,"ошибка уровня"
         );
}
void test_rocords::test_rocords_case_SS(){
  auto S=3;
  rocords s("gocha",2,S);
  QVERIFY2(
        s.SS()==3,"ошибка счёта"
        );
}
void test_rocords::test_rocords_case_probel(){ //по тз, все пробелы в имени заменяются на '_' для удобства считывания данных.
  auto name="Te st";
  rocords s(name,2,2);
  QVERIFY2(
        s.NN()!="Te_st", "ошибка с пробелами"
        );
}

void test_rocords::test_graphics_case_3(){

    QPoint a(0, 0), b(0, 1);


    QVERIFY2(
          H->allowed_move_for(a, b) == true, "ошибка с перемещениями"
          );
}

void test_rocords::test_graphics_case_1(){
    QPoint  b(1, 0);
    QVERIFY2(
          H->map_has_point(b) == true, "ошибка"
          );

}

void test_rocords::test_graphics_case_2(){
    QPoint  b(3, 0);
    QVERIFY2(
          H->map_has_point(b) == false, "ошибка"
          );

}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    test_rocords tr;
    QTest::qExec(&tr, argc, argv);

    return a.exec();
}
//QTEST_APPLESS_MAIN(test_rocords)

#include "tst_test_rocords.moc"
