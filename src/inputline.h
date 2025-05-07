// Copyright (c) 2022-2024 Manuel Schneider

#pragma once
#include <QLineEdit>
#include <albert/inputhistory.h>

// Input method problems: https://bugreports.qt.io/browse/QTBUG-106516
class InputLine : public QLineEdit
{
public:
    InputLine(QWidget *parent);

    void setInputHint(const QString &text);
    void setTriggerLength(uint len);

    void next(bool search);
    void previous(bool search);

    bool clear_on_hide;

private:
    void paintEvent(QPaintEvent *event) override;
    void hideEvent(QHideEvent *event) override;

    QString input_hint_;
    albert::util::InputHistory history_;
    QString user_text_; // used for history search
    uint trigger_length_;

};
