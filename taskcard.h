#ifndef TASKCARD_H
#define TASKCARD_H

#include <QWidget>
#include <QFrame>
#include <QPropertyAnimation>
#include <QLabel>
#include <QToolButton>
#include <QPushButton>

namespace Ui {
class TaskCard;
}

const int animationDuration = 150;
class TaskCard : public QFrame
{
    Q_OBJECT

public:
    explicit TaskCard(QWidget *parent = nullptr);
    QLabel* adressNameL() const;
    QLabel* adressStatusL() const;
    QLabel* adressRecurrencesL() const;
    QLabel* adressDatesL() const;
    QLabel* adressDestinationsL() const;
    QPushButton* adressBackupNowB() const;
    QToolButton* adressEditTB() const;
    QToolButton* adressDeleteTB() const;
    QToolButton* adressFoldingTB() const;
    ~TaskCard();
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
private slots:
    void toggle();
private:
    Ui::TaskCard *ui;
    QWidget *foldedPart;
    QWidget *detailsPart;
    QPropertyAnimation *animation;
};

#endif // TASKCARD_H
