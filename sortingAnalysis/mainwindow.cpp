#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <ctime>
#include <QRandomGenerator>
#include <QMessageBox>
#include <chrono>

int searchMethod = 0;
QVector<int> dataSet;
QString sizeStr;
QString Value;
long long sortTime = 0;
long long searchTime = 0;
int normalSearch(const QVector<int>& dataSet, int value) {
    for (int i = 0; i < dataSet.size(); i++) {
        if (dataSet[i] == value) {
            return i;
        }
    }
    return -1;
}

int binarySearch(const QVector<int>& dataSet, int target) {
    int left = 0;
    int right = dataSet.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (dataSet[mid] == target) {
            return mid;
        } else if (dataSet[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

void mergeSort(QVector<int>& arr, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    QVector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (int i = left, k = 0; i <= right; ++i, ++k) {
        arr[i] = temp[k];
    }
}

bool isSorted(const QVector<int>& dataSet) {
    for (int i = 1; i < dataSet.size(); i++) {
        if (dataSet[i] < dataSet[i-1]) {
            return false;
        }
    }
    return true;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
        // Update label text
    ui->label_6->setText("Search Using: Normal Search");
    searchMethod = 1;

}


void MainWindow::on_pushButton_2_clicked()
{
    ui->label_6->setText("Search Using: Binary Search");
    searchMethod = 2;
}


void MainWindow::on_pushButton_3_clicked()
{
    // Get the dataset size entered by the user
    sizeStr = ui->lineEdit->text();
    int size = sizeStr.toInt();

    // Generate the dataset of positive numbers
    dataSet.clear();
    for (int i = 0; i < size; i++) {
        dataSet.append(QRandomGenerator::global()->bounded(1, size));
    }

    ui->listWidget->clear();
    for (int i = 0; i < dataSet.size(); i++) {
        ui->listWidget->addItem(QString::number(dataSet[i]));
    }

    if (isSorted(dataSet)) {
        ui->label_5->setText("Sorted Array");
    } else {
        ui->label_5->setText("Unsorted Array");
    }

    ui->label_3->setText("The Dataset size is : " + sizeStr);

}
void MainWindow::on_pushButton_4_clicked()
{
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

    mergeSort(dataSet, 0, dataSet.size() - 1);

    std::chrono::steady_clock::time_point then = std::chrono::steady_clock::now();
    sortTime = std::chrono::duration_cast<std::chrono::nanoseconds>(then - now).count();

    ui->listWidget->clear();
        for (int i = 0; i < dataSet.size(); i++) {
            ui->listWidget->addItem(QString::number(dataSet[i]));
        }

        if (isSorted(dataSet)) {
            ui->label_5->setText("Sorted Array");
        } else {
            ui->label_5->setText("Unsorted Array");
        }

        ui->label->setText("Sorting Using: Merge Sort");

}


void MainWindow::on_pushButton_5_clicked()
{
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

    std::sort(dataSet.begin(), dataSet.end());

    std::chrono::steady_clock::time_point then = std::chrono::steady_clock::now();
    sortTime = std::chrono::duration_cast<std::chrono::nanoseconds>(then - now).count();


        // Clear the list widget and add the sorted values
        ui->listWidget->clear();
        for (int i = 0; i < dataSet.size(); i++) {
            ui->listWidget->addItem(QString::number(dataSet[i]));
        }

        if (isSorted(dataSet)) {
            ui->label_5->setText("Sorted Array");
        } else {
            ui->label_5->setText("Unsorted Array");
        }

        ui->label->setText("Sorting Using: STL Sort");

}


void MainWindow::on_pushButton_6_clicked()
{
    if (searchMethod == 1)
    {
        Value = ui->lineEdit_2->text();
        int v = Value.toInt();
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

        int result = normalSearch(dataSet, v);

        std::chrono::steady_clock::time_point then = std::chrono::steady_clock::now();
        searchTime = std::chrono::duration_cast<std::chrono::nanoseconds>(then - now).count();

        if (result == -1) {
            QMessageBox::information(this, "Not Found", "The value was not found in the dataset.\nThe time needed to perform the search in Nanoseconds is: " + QString::number(searchTime) );
        }
        else {
            QMessageBox::information(this, "Found", "The value was found at index " + QString::number(result) + " in the dataset.\nThe time needed to perform the search in Nanoseconds is: " + QString::number(searchTime) + "\nSorting time was: " + QString::number(sortTime));
        }
    }
    else if (searchMethod == 2) // handle binary search
    {
        Value = ui->lineEdit_2->text();
        int v = Value.toInt();

        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

        int result = binarySearch(dataSet, v);

        std::chrono::steady_clock::time_point then = std::chrono::steady_clock::now();
        searchTime = std::chrono::duration_cast<std::chrono::nanoseconds>(then - now).count();


        if (result == -1) {
            QMessageBox::information(this, "Not Found", "The value was not found in the dataset.\nThe time needed to perform the search in Nanoseconds is: " + QString::number(searchTime) );
        }
        else {
            QMessageBox::information(this, "Found", "The value was found at index " + QString::number(result) + " in the dataset.\nThe time needed to perform the search in Nanoseconds is: " + QString::number(searchTime) + "\nSorting time was: " + QString::number(sortTime));
        }
    }
}


