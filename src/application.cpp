#include "application.h"
#include <algorithm>

bool OrderByPriority(Option o1, Option o2)
{
    return o1.priority < o2.priority;
}

bool OrderByCreatedAt(Option o1, Option o2)
{
    return o1.idx < o2.idx;
}

bool Option::matches(bool filterState, int min, int max)
{
    return !filterState || (min <= priority && priority <= max);
}

Application::Application()
{
    const int P_MIN = 1;
    const int P_MAX = 20;

    _screen = Vector2(800, 600);
    genv::gout.open(_screen.x(), _screen.y());
    genv::gout << genv::font("LiberationSans-Regular.ttf", 20);

    genv::gin.timer(1000 / 8);

    // 0
    lbItemName = std::make_shared<Label>("elem neve");
    lbItemName->style.position = {20, 20};
    _ws.push_back(lbItemName);

    // 1
    itemName = std::make_shared<TextInput>();
    itemName->style.position = {20, 50};
    _ws.push_back(itemName);

    // 2
    lbPriority = std::make_shared<Label>("prioritás");
    lbPriority->style.position = {250, 20};
    _ws.push_back(lbPriority);

    // 3
    priority = std::make_shared<NumberPicker>(P_MIN, P_MAX);
    priority->style.position = {250, 50};
    _ws.push_back(priority);

    // 4
    btnAdd = std::make_shared<PushableButton>("Új elem");
    btnAdd->style.position = {20, 100};
    _ws.push_back(btnAdd);

    // 5
    btnDel = std::make_shared<PushableButton>("Töröl");
    btnDel->style.position = {250, 100};
    _ws.push_back(btnDel);

    // 6
    std::vector<std::string> s{""};
    list = std::make_shared<Select>(s);
    list->style.position = {370, 20};
    list->displayMany(5);
    _ws.push_back(list);

    // 7
    btnOrder1 = std::make_shared<PushableButton>("Rendez: prioritás");
    btnOrder1->style.position = {20, 140};
    _ws.push_back(btnOrder1);

    // 8
    btnOrder2 = std::make_shared<PushableButton>("Rendez: létrehozás");
    btnOrder2->style.position = {200, 140};
    _ws.push_back(btnOrder2);

    // 9
    lbFilter = std::make_shared<Label>("Szűrés prioritás intervallumra");
    lbFilter->style.position = {20, 220};
    _ws.push_back(lbFilter);

    // 10
    btnFilter = std::make_shared<CheckBox>("szűrés");
    btnFilter->style.position = {20, 260};
    _ws.push_back(btnFilter);

    // 11
    WminPriority = std::make_shared<NumberPicker>(P_MIN, P_MAX);
    WminPriority->style.position = {130, 250};
    _ws.push_back(WminPriority);

    // 12
    WmaxPriority = std::make_shared<NumberPicker>(P_MIN, P_MAX);
    WmaxPriority->style.position = {230, 250};
    _ws.push_back(WmaxPriority);

    btnAdd->addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self)
                     {
                         if (evt.button == genv::btn_left && self.containsPoint(cursor))
                         {
                             std::string value = itemName->getText();
                             int prior = priority->getValue();
                             if (!value.empty())
                             {
                                 addOption(createOption(value, prior));
                                 updateOptions();
                             }
                         }

                         return false;
                     });

    btnDel->addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self)
                     {
                         if (evt.button == genv::btn_left && self.containsPoint(cursor))
                         {
                             int idx = list->getSelectedIdx();
                             delOption(idx);
                             updateOptions();
                             return true;
                         }
                         return false;
                     });

    WminPriority->addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self)
                           {
                               int prevMinUpper = WminPriority->getUpper();
                               int prevMaxLower = WmaxPriority->getLower();
                               WminPriority->setUpper(WmaxPriority->getValue());
                               WmaxPriority->setLower(WminPriority->getValue());
                               if (prevMinUpper != WminPriority->getUpper() || prevMaxLower != WmaxPriority->getLower())
                               {
                                   updateOptions();
                                   return true;
                               }
                               return false;
                           });

    btnOrder2->addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self)
                        {
                            if (evt.button == genv::btn_left && self.containsPoint(cursor))
                            {
                                std::sort(options.begin(), options.end(), OrderByCreatedAt);
                                updateOptions();
                            }
                            return false;
                        });

    btnFilter->onChange = [&]()
    {
        updateOptions();
    };

    btnOrder1->addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self)
                        {
                            if (evt.button == genv::btn_left && self.containsPoint(cursor))
                            {
                                std::sort(options.begin(), options.end(), OrderByPriority);
                                updateOptions();
                            }
                            return false;
                        });
}

Application::~Application() = default;

bool Application::tick()
{
    genv::gin >> _ev;

    if (_ev.keycode == genv::key_escape)
    {
        return false;
    }

    _screen.clear();

    if (_ev.type == genv::ev_mouse && _ev.button != genv::btn_wheelup && _ev.button != genv::btn_wheelup)
    {
        _cursor = {_ev.pos_x, _ev.pos_y};
    }

    bool focus = true;
    for (auto &w : _ws)
    {
        if (w->handle(_ev, _cursor, focus))
            break;
    }
    for (auto &w : _ws)
    {
        w->draw();
    }

    Vector2(10, 10).move_to();
    Color(255, 0, 0).apply();

    genv::gout << genv::refresh;

    return true;
}

void Application::addOption(Option o)
{
    options.push_back(o);
}

void Application::delOption(int index)
{
    std::vector<Option> result;
    int relIdx = -1;
    for (int i = 0, j = 0; i < options.size(); i++)
    {
        if (options[i].matches(btnFilter->isChecked(), WminPriority->getValue(), WmaxPriority->getValue()))
        {
            if (j == index)
            {
                relIdx = i;
                break;
            }
            j++;
        }
    }
    for(int i = 0; i < options.size(); i++) {
        if (i != relIdx) {
            result.push_back(options[i]);
        }
    }
    options = result;
}

void Application::updateOptions()
{
    std::vector<std::string> v;
    for (Option o : options)
    {
        if (o.matches(btnFilter->isChecked(), WminPriority->getValue(), WmaxPriority->getValue()))
            v.push_back(o.name + " (" + std::to_string(o.priority) + ")");
    }
    if (v.empty())
    {
        v.push_back("");
    }
    list->setOptions(v);
    list->setSelectedIdx(0);
}

Option Application::createOption(std::string name, int priority)
{
    return Option{name, priority, nextIdx++};
}
