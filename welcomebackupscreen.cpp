#include "welcomebackupscreen.h"
#include "settings.h"
#include "ui_welcomebackupscreen.h"

#include <iostream>

#include "taskcard.h"
#include "utils.h"
#include "settings.h"
#include "task.h"


WelcomeBackupScreen::WelcomeBackupScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::welcomeBackupScreen)
{
    ui->setupUi(this);
    loadStyleSheet(":/styles/backupScreen.css", ui->newTaskW);

    Settings& settings = Settings::getInstance();
    std::vector<Task> tasks = settings.getTaskVec();
    QLayout *layout = ui->scrollAreaWidgetContents->layout();

    for (auto& task : tasks) {
        addTaskToLayout(task, layout, settings);
    }
}

WelcomeBackupScreen::~WelcomeBackupScreen()
{
    delete ui;
}
void WelcomeBackupScreen::addTaskToLayout(const Task& task, QLayout* layout, Settings& settings) {
    std::vector<std::shared_ptr<Schedule>> schedules = task.getSchedules();
    std::vector<std::string> destinations = task.getDestinations();
//    auto firstDest = settings.getKeyDests(destinations[0])[0];
    auto firstRec = schedules[0]->getRecurrence();
    std::string firstRecString = getRecurrenceString(firstRec);

    TaskCard *card = new TaskCard(this);
    card->adressNameL()->setText(QString::fromStdString(task.getName()));
    card->adressStatusL()->setText(QString("Waiting"));
    card->adressRecurrencesL()->setText(QString::fromStdString(firstRecString));
    card->adressDatesL()->setText(QString("Date"));
//    card->adressDestinationsL()->setText(QString::fromStdString(firstDest));

    static_cast<QVBoxLayout*>(layout)->addWidget(card);
    static_cast<QVBoxLayout*>(layout)->addSpacerItem(new QSpacerItem(15, 15, QSizePolicy::Fixed, QSizePolicy::Fixed));
}
std::string WelcomeBackupScreen::getRecurrenceString(ScheduleRecurrence recurrence) {
    switch (recurrence) {
    case ScheduleRecurrence::ONCE: return "Once";
    case ScheduleRecurrence::DAILY: return "Every day";
    case ScheduleRecurrence::WEEKLY: return "Every week";
    case ScheduleRecurrence::MONTHLY: return "Every month";
    default: return "";
    }
}
