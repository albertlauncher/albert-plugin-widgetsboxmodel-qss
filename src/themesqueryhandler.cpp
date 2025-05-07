// Copyright (c) 2022-2025 Manuel Schneider

#include "themesqueryhandler.h"
#include "window.h"
#include <albert/albert.h>
#include <albert/matcher.h>
#include <albert/standarditem.h>
using namespace albert;
using namespace std;
using namespace util;

ThemesQueryHandler::ThemesQueryHandler(Window *w) : window(w) {}

QString ThemesQueryHandler::id() const
{ return QStringLiteral("widgetboxmodel_themes"); }

QString ThemesQueryHandler::name() const
{ return QStringLiteral("Themes"); }

QString ThemesQueryHandler::description() const
{ return Window::tr("Switch themes"); }

QString ThemesQueryHandler::defaultTrigger() const { return "theme "; }

void ThemesQueryHandler::handleTriggerQuery(Query &query)
{
    vector<Action> actions;

    Matcher matcher(query);

    for (const auto &[name, path] : window->themes)
        if (auto m = matcher.match(name); m)
        {
            actions.clear();

            actions.emplace_back("setlight",
                                 Window::tr("Use in light mode"),
                                 [&]{ window->setLightTheme(name); },
                                 false);

            actions.emplace_back("setdark",
                                 Window::tr("Use in dark mode"),
                                 [&]{ window->setDarkTheme(name); },
                                 false);

            if (window->darkMode())
                std::swap(actions[0], actions[1]);

            actions.emplace_back("open", Window::tr("Open theme file"), [p = path] { open(p); });

            query.add(StandardItem::make(QString("theme_%1").arg(name),
                                         name,
                                         path,
                                         name,
                                         {QStringLiteral("gen:?&text=🎨")},
                                         actions));
        }
}
