#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <QMainWindow>
#include <vector>  // Include the necessary header for std::vector
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class SudokuSolver; }
QT_END_NAMESPACE

class SudokuSolver : public QMainWindow
{
    Q_OBJECT

public:
    SudokuSolver(QWidget *parent = nullptr);
    ~SudokuSolver();

private slots:
    void solveSudoku();

private:
    Ui::SudokuSolver *ui;

    // Add any additional member variables or methods needed
    bool isAllowed(std::vector<std::vector<int>> &sudoku, int x, int y, int val);
    bool solvesudoku(std::vector<std::vector<int>> &sudoku, int i, int j);
    // ... other member variables or methods ...

};

#endif // SUDOKUSOLVER_H

