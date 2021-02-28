# ⚛ Tugas Kecil 2 Strategi Algoritma (IF-2211) ⚛

## 💢 Deskripsi

Tugas membuat program(SUPREMO PLAN) topological sorting untuk penyusunan rencana kuliah

## 💢 How To Use

1. Run this command

```shell
$ g++ ./src/tucil2.cpp -o ./bin/tucil2
```

2. Navigate to src folder

```shell
$ cd ./src
```

3. Run this command

```shell
$ ./tucil2
OR
$ tucil2.exe
```

## 💢 Algoritma
```shell
1.	Buat representasi DAG(Directed Acyclic Graph) dan representasi untuk menyimpan nilai derajat masuk dari setiap simpul / vertices
2.	Pilih semua simpul / vertices yang memiliki derajat masuk sebesar 0 lalu buang simpul-simpul tersebut dari graf.
3.	Lakukan perubahan derajat masuk kepada simpul / vertices dengan mengurangi derajat simpul-simpul tersebut yang berhubungan dengan simpul yang dibuang dari graf.
4.	Ulangi langkah (2) dan (3) hingga graf kosong, jika graf sudah kosong maka algoritma pengurutan sudah selesai.
```

## 💢 Additional

<ul>
  <li>To add new testcase, go to test folder and create new .txt file</li>
</ul>

## 💢 Example Input and Output

```shell
============== WELCOME TO SUPREMO PLAN APPLICATION ==============

Masukkan nama file: test9.txt

Semester I : C6, C1, C8, C3
Semester II : C4, C10, C2
Semester III : C5
Semester IV : C7
Semester V : C9

Time : 0.02s
```

## 💢 Made by

<ul>
  <li>Karel Renaldi - 13519180 - K04</li>
</ul>
