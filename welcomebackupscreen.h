#ifndef WELCOMEBACKUPSCREEN_H
#define WELCOMEBACKUPSCREEN_H

#include <QWidget>

#include "settings.h"
#include "task.h"

namespace Ui {
class welcomeBackupScreen;
}

class WelcomeBackupScreen : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeBackupScreen(QWidget *parent = nullptr);
    ~WelcomeBackupScreen();

private:
    Ui::welcomeBackupScreen *ui;
    void addTaskToLayout(const Task& task, QLayout* layout, Settings& settings);

    std::string getRecurrenceString(ScheduleRecurrence recurrence);
};

#endif // WELCOMEBACKUPSCREEN_H
