# algos_2# algos_2 task_7
Біноміальне дерево - дерево, що задається рекурентно. B0 - це просто вершина. Ві - це Ві-1, лівим сином якого зробили Ві-1.
Властивості біноміальних дерев:
1) 2^k вершин
2) Висота дерева рівна k
3) С з і по k (біноміальний коефіцієнт) - кількість вершин глибини і
4) діти Ві - це Ві-1, Ві-2, ... ,В0
5) Максимальна висота вершини дерева Вn рівна O(log N)

Біноміальна куча - це множина біноміальних дерев з певними властивостями: 
1)У кожному біноміальному дереві зберігається властивість кучі; 
2)Нема двох дерев однакового розміру; 
3)Дерева впорядковані за розміром; 

Зберігаємо дерево таким чином:ключ вершини,кількість її синів (ступінь вершини), правий брат та лівий син.

Реалізовані операції:

Порівняння двох вершин за кількістю їх синів

Злиття двох дерев одного ступеню в одне. Дерево з більшим ключем вершини стає лівим сином іншого

Злиття усіх дерев однакового ступеню в кучі. Проходимо по кучі (по вершинах дерев) і зливаємо однакові за допомогою описаної вище процедури. При пошуку однакових за вступенем дерев можемо отримати такі випадки:
1)Тільки 2 дерева однакового разміру. Тоді об'єднуємо їх.
2)3 дерева однакового разміру. Об'єднуємо 2 останніх. Для цього в реалізаціі завжди звіряємо три послідовних дерева.
Складність: (O(log N ))

Розвертання списку у інший бік. Знадобиться далі для видалення вершини.

Об'єднання двох куч в одну (два списка дерев в один зберігаючи правило неспадання ступеня вершин дерев). Алгоритм аналогічний злиттю в mergeSort: Зберігаємо по вказівнику на початки списків і в результуючий список записуємо вершину з меншим (не більшим) ступенем, той з якого щойно записали зміщуємо на наступний елемент. Час роботи O(list1.length) + O(list2.length) = O(log N).

Додавання нового елементу в кучу. Алгоритм: Створюємо кучу з одного елемента і об'єднуємо с нашою кучею. Складність: O(1) + O(log(N)) = O(log(N)).

Знаходження мінімуму в кучі. Алгоритм: очевидно, що мінимум знаходиться в списку коренів, тобто щоб його знайти потрібно пройтись по списку коренів. Складність: O(list.length) = O(log(N)).

Видалення мінімального элементу. Знаходимо його за допомогою попередньої процедури. Видаляємо його зі списку коренів. З перевернутого списку дітей видаленої вершини робимо нову кучу і об'єднуємо з початковою. Складність: так як кожна операція працює за O(log N): O(log N) + O(log N) + O(log N) = O(log N)
