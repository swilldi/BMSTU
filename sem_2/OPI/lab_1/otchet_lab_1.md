1. В домашней папке создали папку OPI_lab_1 и перешли в неё
```bash
dmitriy@fedora:~$ mkdir OPI_lab_1
dmitriy@fedora:~$ cd OPI_lab_1/
```
2. Проверили содержимое папки OPI_lab_1
```bash
dmitriy@fedora:~/OPI_lab_1$ pwd
/home/dmitriy/OPI_lab_1
```
3. В созданной папке создали локальный репозиторий при помощи команды `git init` и проверили, что папке не пустая
```bash
dmitriy@fedora:~/OPI_lab_1$ git init
hint: Using 'master' as the name for the initial branch. This default branch name
hint: is subject to change. To configure the initial branch name to use in all
hint: of your new repositories, which will suppress this warning, call:
hint:
hint: 	git config --global init.defaultBranch <name>
hint:
hint: Names commonly chosen instead of 'master' are 'main', 'trunk' and
hint: 'development'. The just-created branch can be renamed via this command:
hint:
hint: 	git branch -m <name>
Инициализирован пустой репозиторий Git в /home/dmitriy/OPI_lab_1/.git/
dmitriy@fedora:~/OPI_lab_1$ ls -a
.  ..  .git
```
4. Проверили, что задано имя пользователя (user.name) и адрес электронной почты (user.email)
```bash
dmitriy@fedora:~/OPI_lab_1$ git config -l
user.email=dimitruo@yandex.ru
user.name=Dmitriy
core.repositoryformatversion=0
core.filemode=true
core.bare=false
core.logallrefupdates=true
```
5. Поместили исходный код программы в рабочую папку и проверили наличие файлов программы 
```bash
dmitriy@fedora:~/OPI_lab_1$ cp -rf /home/dmitriy/Downloads/Рабочие\ материалы-20250211/src_1/* .
dmitriy@fedora:~/OPI_lab_1$ ls
iarray.py  main.py
```
6. запустили `main.py`, в итоге в папке OPI_lab_1 появилась \_\_pycache\_\_
```bash
dmitriy@fedora:~/OPI_lab_1$ ls
iarray.py  main.py  __pycache__
```
7. Создали файл .gitignore и добавили в него "**/\_\_pycache\_\_/**"
```bash
dmitriy@fedora:~/OPI_lab_1$ touch .gitignore
dmitriy@fedora:~/OPI_lab_1$ nano .gitignore
```
8. При помощи `git status` проверили, что \_\_pycache\_\_ будет игнорироваться
```bash
dmitriy@fedora:~/OPI_lab_1$ git status
Текущая ветка: master

Еще нет коммитов

Неотслеживаемые файлы:
  (используйте «git add <файл>...», чтобы добавить в то, что будет включено в коммит)
	.gitignore
	iarray.py
	main.py

индекс пуст, но есть неотслеживаемые файлы
(используйте «git add», чтобы проиндексировать их)
```
9. Добавили в коммит файл .gitignore и проверили файлы текщего коммита
```bash
dmitriy@fedora:~/OPI_lab_1$ git add .gitignore 
dmitriy@fedora:~/OPI_lab_1$ git status
Текущая ветка: master

Еще нет коммитов

Изменения, которые будут включены в коммит:
  (используйте «git rm --cached <файл>...», чтобы убрать из индекса)
	новый файл:    .gitignore

Неотслеживаемые файлы:
  (используйте «git add <файл>...», чтобы добавить в то, что будет включено в коммит)
	iarray.py
	main.py
```
10. Зафиксировали изменения текущей версии
```bash
dmitriy@fedora:~/OPI_lab_1$ git commit -m ".gitignore was added"
[master (корневой коммит) 1501ef3] .gitignore was added
 1 file changed, 1 insertion(+)
 create mode 100644 .gitignore
```
11. Добавили в контроль версий саму программу, проверили состояние текущей версии и зафиксировали изменения
```bash
dmitriy@fedora:~/OPI_lab_1$ git add main.py iarray.py 
dmitriy@fedora:~/OPI_lab_1$ git status
Текущая ветка: master
Изменения, которые будут включены в коммит:
  (используйте «git restore --staged <файл>...», чтобы убрать из индекса)
	новый файл:    iarray.py
	новый файл:    main.py

dmitriy@fedora:~/OPI_lab_1$ git commit -m "Programm files was added"
[master 83ea78d] Programm files was added
 2 files changed, 48 insertions(+)
 create mode 100644 iarray.py
 create mode 100644 main.py
```
12. В main.py добавили test_2, который демонстрирует, что алгоритм работает не правильно
| Input | Output |
|-------|--------|
| -1 -2 -3 -4 -5, 5| -2 -4|
13. Проверили состояние, после добавления теста
```bash
dmitriy@fedora:~/OPI_lab_1$ git status
Текущая ветка: master
Изменения, которые не в индексе для коммита:
  (используйте «git add <файл>...», чтобы добавить файл в индекс)
  (используйте «git restore <файл>...», чтобы отменить изменения в рабочем каталоге)
	изменено:      .gitignore
	изменено:      main.py

индекс пуст (используйте «git add» и/или «git commit -a»)
```
14. Проверили изменения по сравнению с предыдущим коммитом
```bash
dmitriy@fedora:~/OPI_lab_1$ git diff
diff --git a/.gitignore b/.gitignore
index 59ee0a5..cffb5b1 100644
--- a/.gitignore
+++ b/.gitignore
@@ -1 +1,2 @@
 **/__pycache__/**
+**/.idea/**
diff --git a/main.py b/main.py
index 3a6c425..4c2f73d 100644
--- a/main.py
+++ b/main.py
@@ -11,12 +11,26 @@ def test_1():
   
   return arr, 5
 
+def test_2():^M
+  arr = [-1, -2, -3, -4, -5]^M
+^M
+  return arr, len(arr)^M
+^M
```
15. В результате main.py находиться в состоянии *modifided*. Изменения: из старой версии удалены строки с 11 по 12, а в новой версии добавлены с 11 по 26.
16. Зафиксированные изменения main.py. Номер ревизии: 5243646. Комментарий при коммите: test with wrong answer was added
17. Создан отчет по ошибке в разделе issue на платформе GitLub. Указаны ввохдные данные при которых возникает ошибка, указананна функция, её модуль и номер ревизии.
18. В файле iarray.py исправлена функция form_array
19. Проведен анализ изменений при помощи git status и git diff. Файл iarray.py имеет статус modifided, были добавлены строки с 6 по 8
```bash
dmitriy@fedora:~/OPI_lab_1$ git status
Текущая ветка: master
Изменения, которые не в индексе для коммита:
  (используйте «git add <файл>...», чтобы добавить файл в индекс)
  (используйте «git restore <файл>...», чтобы отменить изменения в рабочем каталоге)
	изменено:      iarray.py

индекс пуст (используйте «git add» и/или «git commit -a»)
dmitriy@fedora:~/OPI_lab_1$ git diff
diff --git a/iarray.py b/iarray.py
index 63b016d..69afede 100644
--- a/iarray.py
+++ b/iarray.py
@@ -6,6 +6,8 @@ def form_array(arr, n):
     if (new_arr[i] < 0):
       new_arr.pop(i)
       n -= 1
+^M
+      i -= 1^M
     
     i += 1
```
20. В коммит добавлен файл iarray.py. Совершен коммит с коментарием: "form_array was fixed" и контрольной суммой: 4262a17