#include "sudokusolver.h"
#include "ui_sudokusolver.h"
#include <bits/stdc++.h>
#include <QDebug>
using namespace :: std;

SudokuSolver::SudokuSolver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SudokuSolver)
{
    ui->setupUi(this);

    // Connect the "clicked" signal of the Submit button to a custom slot
    connect(ui->button, &QPushButton::clicked, this, &SudokuSolver::solveSudoku);
}

SudokuSolver::~SudokuSolver()
{
    delete ui;
}

// Checks if a value is allowed at a given cell (x, y)
bool SudokuSolver::isAllowed(vector<vector<int> > &sudoku, int x, int y, int val){
    // check if the cloumn has val already
    for(int i=0; i<9; i++){
        if(sudoku[i][y]==val){
            return false;
        }
    }

    // check if the row has val already
    for(int i=0; i<9; i++){
        if(sudoku[x][i]==val){
            return false;
        }
    }

    // check if the sub grid (3X3 matrix) of the current cell has the val already
    int xx = (x/3)*3;   // --> starting row index of current cell subgrid
    int yy = (y/3)*3;	// --> starting column index of current cell subgrid

    for(int i=xx; i<xx+3; i++){
        for(int j=yy; j<yy+3; j++){
            if(sudoku[i][j]==val){
                return false;
            }
        }
    }

    return true;
}

bool SudokuSolver::solvesudoku(vector<vector<int> > &sudoku, int i, int j){
    // Base Case: Print the sudoku when you've reached the end of all rows (0-8)
    if(i==9){
        return true;
    }

    // Move to the next row when you reach the end of a row
    if(j==9){
        return solvesudoku(sudoku, i+1, 0);
    }

    if(sudoku[i][j]==-1) return false;

    // If the current cell is already filled, move to the next cell
    if(sudoku[i][j]!=0){
        return solvesudoku(sudoku, i, j+1);
    }

    for(int val=1; val<=9; val++){
        if(isAllowed(sudoku, i, j, val)){
            sudoku[i][j]=val;
            int success = solvesudoku(sudoku, i, j+1);  // returns if solution if possible the remaining sudoku with current val placed at (i, j)
            if(success){
                return true;
            }
            sudoku[i][j]=0;   // backtrack if the solution is not found
        }
    }

    return false;
}

void SudokuSolver::solveSudoku()
{
    // Extract input values from the line edit widgets in the UI
    std::vector<std::vector<int>> sudokuMatrix(9, std::vector<int>(9, 0));

    QMessageBox::information(this, "Computing...", "Fetching Results");

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            QLineEdit *lineEdit = qobject_cast<QLineEdit *>(ui->gridLayout->itemAtPosition(i, j)->widget());

            if (lineEdit) {
                QString cellValue = lineEdit->text();

                int inputValue = cellValue.toInt();
                qDebug() << "Cell (" << i << "," << j << ") Value:" << inputValue;
                if (inputValue >= 1 && inputValue <= 9) {
                    sudokuMatrix[i][j] = inputValue;
                } else{
                    sudokuMatrix[i][j] = 0;
                }
            } else {
                QMessageBox::information(this, "Invalid Sudoku", "The entered Sudoku is invalid!");
                return;
            }

        }
    }

    // Check if the provided sudoku is valid
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(sudokuMatrix[i][j]!=0){
                if(!isAllowed(sudokuMatrix, i, j, sudokuMatrix[i][j])){
                    QMessageBox::information(this, "Invalid Sudoku", "The entered Sudoku is invalid!");
                    return;
                }
            }
        }
    }

    bool solution = solvesudoku(sudokuMatrix, 0, 0);
    qDebug() << solution;

    if (solution) {
        // Populate the solved Sudoku values back to the UI grid
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                QLineEdit *lineEdit = qobject_cast<QLineEdit *>(ui->gridLayout->itemAtPosition(i, j)->widget());

                if (lineEdit) {
                    lineEdit->setText(QString::number(sudokuMatrix[i][j]));
                }
            }
        }
    } else {
        // Display a pop-up message if the Sudoku is invalid
        QMessageBox::information(this, "Invalid Sudoku", "The entered Sudoku is invalid!");
    }
}

