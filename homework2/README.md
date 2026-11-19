Собрать и запустить:
g++ -std=c++17 -Wall -Wextra main.cpp -o physcat

Все файлы:

"Errors.hpp", "Inventory.hpp", "Transport.hpp", "Things.hpp", "ServiceCenter.hpp", "Registry.hpp", "Park.hpp", "main.cpp".

Схема наследования:
Item
  ├─ Transport

  │     ├─ Bike

  │     ├─ EBike : Transport, Powered

  │     └─ Scooter : Transport, Powered

  ├─ Helmet

  └─ Dock : Item, Powered

Item - всё, что на балансе, Transport - транспорт, Powered - предмет, использующий электроэнергию

Умные указатели:

1. unique_ptr - используется в Park::AddTransport(std::unique_ptr<Transport> t) - объект живет пока идет техосмотр, если он оказался "broken", то unique_ptr умирает вместе с объектом, а если объект прошел техосмотр, то владение им передается в вещи: items_.push_back(std::move(t)).
2. shared_ptr - используется в Park::specs_ и Transport::spec_, которые хранят shared_ptr<Spec>, т.к. может несколько объектов одной модели.
3. weak_ptr - используется в Park::focus_ - витрина; после удаления (с помощью remove) focus_.lock() вернет либо shared_ptr, либо null_ptr (в этом случае show_focus напечатает removed)

Исключения:

std::runtime_error

       ├─ InspectionRejected - техосмотр отклонил из-за наличия "broken"

       ├─ BadArg - "плохие" аргументы (пустой id, simplicity вне [1,10], энергия меньше 0,

       │           неизвестная команда, дубликат id, переполненный реестр

       └─ NotFound - после команд focus, remove, info идет несуществующий id


Шаблоны:

Класс template <class T, int Cap> class Reg — вместо T могут быть Spec, Scooter, Item и т.д.

template <int Cap> сlass Reg<std::shared_ptr<Spec>, Cap> - специализация для T = std::shared_ptr<Spec>

Функция TotalEnergy(items), суммирующая Energy() у всех Powered элементов.

Креатив:

команды: avg_energy, info, rename, specs, 

Перегрузки:

operator<< печатает id name
operator< сортирует по id 
operator== сравнивает по id

Все команды:

add … - добавить позицию (см. таблицу ниже)

list - все позиции, отсортированные по id

novice - прокат с simplicity ≥ 6

energy - суммарный суточный расход

focus id - поставить позицию на витрину

show_focus - напечатать витрину или removed

remove id - убрать позицию из парка

specs - список моделей

stats - отчет: count и energy

count - число позиций

quit - выход

info id - информация о позиции (название, модель)

avg_energy - печать средней энергии по Powered объектам

rename id newname - переименовать объект по id


Добавление:

add scooter id name energy score - электросамокат (транспорт)

add ebike id name energy score - электровелосипед (транспорт)

add bike id name score - обычный велосипед (транспорт)

add helmet id name - шлем (вещь)

add dock id name energy - док-станция (вещь)

Использование ИИ:

ИИ использовалось для написания перегрузки operator<<, идеи создания DoAdd в main для более простой записи добавления, тестирования программы и форматирования кодстайла.
