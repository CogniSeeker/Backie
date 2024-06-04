#include "utils.h"
#include "taskcard.h"
#include "ui_taskcard.h"

TaskCard::TaskCard(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TaskCard)
{
    ui->setupUi(this);

    loadStyleSheet(":/styles/taskCard.css", ui->stylingTaskCardWidget);

    detailsPart = ui->detailsCardPart;
    foldedPart = ui->foldedCardPart;

    detailsPart->setMaximumHeight(0);

    animation = new QPropertyAnimation(detailsPart, "maximumHeight", this);
    animation->setDuration(animationDuration);

    // capture click events for the folded part of card
    foldedPart->installEventFilter(this);
}

TaskCard::~TaskCard()
{
    delete ui;
}
void TaskCard::toggle() {
    if (detailsPart->maximumHeight() == 0) {
        animation->setStartValue(0);
        animation->setEndValue(150);
    } else {
        animation->setStartValue(150);
        animation->setEndValue(0);
    }
    animation->start();
}
bool TaskCard::eventFilter(QObject *watched, QEvent *event) {
    if (watched == foldedPart && event->type() == QEvent::MouseButtonPress) {
        toggle();
        return true;
    }
    return QWidget::eventFilter(watched, event);
}
QLabel* TaskCard::adressNameL() const {
    return ui->taskNameL;
}
QLabel* TaskCard::adressStatusL() const {
    return ui->taskStatusL;
}
QLabel* TaskCard::adressRecurrencesL() const {
    return ui->recurrenceSumTasksL;
}
QLabel* TaskCard::adressDatesL() const {
    return ui->dateSumTasksL;
}
QLabel* TaskCard::adressDestinationsL() const {
    return ui->destinationsSumTasksL;
}
QPushButton* TaskCard::adressBackupNowB() const {
    return ui->backupNowTaskB;
}
QToolButton* TaskCard::adressEditTB() const {
    return ui->editTaskTB;
}
QToolButton* TaskCard::adressDeleteTB() const {
    return ui->deleteTaskTB;
}
QToolButton* TaskCard::adressFoldingTB() const {
    return ui->foldingTaskTB;
}
