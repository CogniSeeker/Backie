#ifndef BACKUPSCREEN_H
#define BACKUPSCREEN_H

#include <QWidget>
#include <filesystem>
#include <vector>
#include <variant>

#include "backupschedule.h"

class BackupArgs {
private:
    BackupType backupType;
    std::filesystem::path sourceBackupDirPath = "";
    ScheduleRecurrence backupRecurrence = ScheduleRecurrence::DAILY;
    std::array<int, 6> dateArgs = {-1, -1, -1, -1, -1, -1};

public:
    enum DateArgs {
        YEAR,
        MONTH,
        DAYOFWEEK,
        DAYOFMONTH,
        HOUR,
        MINUTE,
    };

    void clear();

    void setDate(DateArgs type, int value);
    int getDate(DateArgs type) const;

    void setPath(const std::filesystem::path& path);
    QString getPathQString();

    void setBackupType(BackupType type);
    BackupType getBackupType();

    void setBackupRecurrence(ScheduleRecurrence recurrence);
    ScheduleRecurrence getBackupRecurrence();
};

namespace Ui {
class BackupScreen;
}

class BackupScreen : public QWidget
{
    Q_OBJECT

public:
    explicit BackupScreen(QWidget *parent = nullptr);
    ~BackupScreen();

private slots:

    void browseForSourceFolder();
    void onSourcePathEdited(const QString& newPath);

    void on_selectDateB_clicked();

    void handleRadioButtonToggle(bool isChecked);
    void handleComboBoxIndexChanged(int index);

    void updateChosenDateLabel(BackupArgs date);
    void printOutDateArgs(std::vector<int> dateArgs);
    QString addZero(int number);

private:
    Ui::BackupScreen *ui;
    BackupArgs backupArgs;
};

#endif // BACKUPSCREEN_H
