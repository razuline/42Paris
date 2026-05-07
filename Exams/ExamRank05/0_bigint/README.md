# ExamRank05: Bigint (Arbitrary Precision)

## 📌 Concept
Standard types have limits. `bigint` uses `std::vector<int>` to store digits of any length. It tests the ability to manage memory, understand data representation, and master operator overloading.
* **Storage:** Digits are stored in **reverse order** (until at index 0). `1337` becomes `{7, 3, 3, 1}`.

* **Addition:** Simulates "column addition" with a `carry` variable.

* **Shifts:** `<<` inserts zeros at the beginning of the vector; `>>` erases elements from the beginning.

## 1️⃣​ Data Representation: Why Reverse?
A `bigint` is used to store numbers larger than standard types like `unsigned long long` can handle. The code uses a `std::vector<int>` to store each digit.

### **The Secret: Reverse Storage**

In the code, the number `1337` is stored as `{7, 3, 3, 1}`.
* **Index 0** always holds the "ones" column ($10^0$).

* **Index 1** holds the "tens" column ($10^1$).

### **Why do we do this?**

When we add numbers by hand (column addition), we always start from the right (the ones). By storing them in reverse, the "ones" are always at the start of your vector (`[0]`), making it easy to align two numbers and handle "carries".

## 2️⃣​ The Mechanics of Addition (`+=`)
This operator mimics the way we were taught to add in school.
* **Iteration:** We loop through the digits of both numbers simultaneously.

* **The Carry:** If the sum of two digits is $10$ or more (e.g., $7 + 5 = 12$), we keep the $2$ at the current position and "carry" the $1$ over to the next position.

* **Dynamic Growth:** If the addition creates a new digit at the very end (like $9 + 1 = 10$), the vector grows to accommodate the new "1".