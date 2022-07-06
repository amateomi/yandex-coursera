/*
 * Реализуйте класс TeamTasks, позволяющий хранить статистику по статусам задач
 * команды разработчиков:
 *
 * // Перечислимый тип для статуса задачи
 * enum class TaskStatus {
 *   NEW,          // новая
 *   IN_PROGRESS,  // в разработке
 *   TESTING,      // на тестировании
 *   DONE          // завершен
 * };
 *
 * // Объявляем тип-синоним для map<TaskStatus, int>,
 * // позволяющего хранить количество задач каждого статуса
 * using TasksInfo = map<TaskStatus, int>;
 *
 * class TeamTasks {
 *  public:
 *   // Получить статистику по статусам задач конкретного разработчика
 *   const TasksInfo& GetPersonTasksInfo(const string& person) const;
 *
 *   // Добавить новую задачу (в статусе NEW) для конкретного разработчика
 *   void AddNewTask(const string& person);
 *
 *   // Обновить статусы по данному количеству задач конкретного разработчика,
 *   // подробности см. ниже
 *   tuple<TasksInfo, TasksInfo> PerformPersonTasks(
 *       const string& person, int task_count);
 * };
 *
 * Метод PerformPersonTasks должен реализовывать следующий алгоритм:
 * 1. Рассмотрим все невыполненные задачи разработчика person.
 * 2. Упорядочим их по статусам: сначала все задачи в статусе NEW, затем все
 *    задачи в статусе IN_PROGRESS и, наконец, задачи в статусе TESTING.
 * 3. Рассмотрим первые task_count задач и переведём каждую из них в следующий
 *    статус в соответствии с естественным порядком:
 *    NEW → IN_PROGRESS → TESTING → DONE.
 * 4. Вернём кортеж из двух элементов: информацию о статусах обновившихся задач
 *    (включая те, которые оказались в статусе DONE) и информацию о статусах
 *    остальных не выполненных задач.
 *
 * В случае отсутствия разработчика с именем person метод PerformPersonTasks
 * должен вернуть кортеж из двух пустых TasksInfo
 * Гарантируется, что task_count является положительным числом. Если task_count
 * превышает текущее количество невыполненных задач разработчика, достаточно
 * считать, что task_count равен количеству невыполненных задач: дважды
 * обновлять статус какой-либо задачи в этом случае не нужно.
 * Кроме того, гарантируется, что метод GetPersonTasksInfo не будет вызван для
 * разработчика, не имеющего задач.
 *
 * Пример работы метода PerformPersonTasks
 * Предположим, что у конкретного разработчика имеется 10 задач со следующими статусами:
 * - NEW — 3
 * - IN_PROGRESS — 2
 * - TESTING — 4
 * - DONE — 1
 * Поступает команда PerformPersonTasks с параметром task_count = 4, что
 * означает обновление статуса для 3 задач c NEW до IN_PROGRESS и для 1 задачи с
 * IN_PROGRESS до TESTING.
 * Если выписать статусы всех задач по порядку, а обновляемые заключить в
 * квадратные скобки, то изменение можно изобразить следующим образом:
 * [NEW, NEW, NEW, IN_PROGRESS,] IN_PROGRESS, TESTING, TESTING, TESTING, TESTING, DONE
 * ==>
 * [IN_PROGRESS, IN_PROGRESS, IN_PROGRESS, TESTING,] IN_PROGRESS, TESTING, TESTING, TESTING, TESTING, DONE
 *
 * Таким образом, новые статусы задач будут следующими:
 * - IN_PROGRESS — 3 обновлённых, 1 старая
 * - TESTING — 1 обновлённая, 4 старых
 * - DONE — 1 старая
 * В этом случае необходимо вернуть кортеж из 2 словарей:
 * - Обновлённые задачи: IN_PROGRESS — 3, TESTING — 1.
 * - Не обновлённые задачи, исключая выполненные: IN_PROGRESS — 1, TESTING — 4.
 *
 * Ни один из словарей не должен содержать лишних элементов, то есть статусов,
 * которым соответствует ноль задач.
 * По условию, DONE задачи не нужно возвращать в не обновлённых задачах
 * (untouched_tasks).
 *
 * Примечание
 * Обновление словаря одновременно с итерированием по нему может привести к
 * непредсказуемым последствиям. При возникновении такой необходимости
 * рекомендуется сначала в отдельном временном словаре собрать информацию об
 * обновлениях, а затем применить их к основному словарю.
 */
#include <iostream>
#include <map>

using namespace std;

enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

TaskStatus Next(const TaskStatus& task_status) {
  return static_cast<TaskStatus>(
      static_cast<int>(task_status) + 1
  );
}

using TasksInfo = map<TaskStatus, int>;

void DeleteZeros(TasksInfo& tasks) {
  auto status = TaskStatus::NEW;
  while (true) {
    if (tasks.count(status) == 1 && tasks[status] == 0) {
      tasks.erase(status);
    }
    if (status == TaskStatus::DONE) {
      break;
    }
    status = Next(status);
  }
}

class TeamTasks {
 public:
  [[nodiscard]]
  const TasksInfo& GetPersonTasksInfo(const string& person) const {
    return data_.at(person);
  }

  void AddNewTask(const string& person) {
    ++data_[person][TaskStatus::NEW];
  }

  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count) {

    TasksInfo& tasks = data_[person];

    TasksInfo updated_tasks;
    for (auto status = TaskStatus::NEW;
         status != TaskStatus::DONE;
         status = Next(status)) {
      updated_tasks[Next(status)] = min(task_count, tasks[status]);
      task_count -= updated_tasks[Next(status)];
    }

    TasksInfo untouched_tasks;
    for (auto status = TaskStatus::NEW;
         status != TaskStatus::DONE;
         status = Next(status)) {
      untouched_tasks[status] = tasks[status] - updated_tasks[Next(status)];
    }

    for (auto status = TaskStatus::NEW;
         status != TaskStatus::DONE;
         status = Next(status)) {
      tasks[status] -= updated_tasks[Next(status)];
      tasks[Next(status)] += updated_tasks[Next(status)];
    }

    DeleteZeros(updated_tasks);
    DeleteZeros(untouched_tasks);
    DeleteZeros(tasks);

    return tie(updated_tasks, untouched_tasks);
  }

 private:
  map<string, TasksInfo> data_;
};

void PrintTasksInfo(TasksInfo tasks_info) {
  cout << "size: " << tasks_info.size() <<
       ", " << tasks_info[TaskStatus::NEW] << " new tasks" <<
       ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
       ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
       ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
  TeamTasks tasks;
  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  TasksInfo updated_tasks, untouched_tasks;

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
}

