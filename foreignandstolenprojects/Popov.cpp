#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <random>
#include <limits>
#include <iostream>
#include <iomanip>

class Matrix
{
private:
    std::size_t N;
    double** elems;
public:
    Matrix();
    Matrix(const std::size_t& N);
    Matrix(const Matrix& m);
    Matrix(Matrix&& m);
    Matrix(const std::size_t& N, std::mt19937& genrand);

    ~Matrix();

    Matrix& operator= (const Matrix& m);
    Matrix& operator= (Matrix&& m);
    Matrix& operator+= (const Matrix& m);
    Matrix& operator-= (const Matrix& m);

    template<typename Type>
    Matrix& operator*= (const Type& a);

    template<typename Type>
    Matrix& operator/= (const Type& a);

    friend Matrix operator+ (const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator- (const Matrix& lhs, const Matrix& rhs);

    void display();
};

Matrix::Matrix()
{
    this->N = 0;
    this->elems = nullptr;
}

Matrix::Matrix(const std::size_t& N)
{
    this->N = N;
    this->elems = new double* [N];
    for ( auto i = 0; i < this->N; ++i ) {
        this->elems[i] = new double [N];
    }
}

Matrix::Matrix(const Matrix& m)
{
    this->N = m.N;
    this->elems = new double* [N];
    for ( auto i = 0; i < this->N; ++i ) {
        this->elems[i] = new double [N];
        for ( auto j = 0; j < this->N; ++j ) {
            this->elems[i][j] = m.elems[i][j];
        }
    }
}

Matrix::Matrix(Matrix&& m)
{
    this->N = std::move(m.N);
    this->elems = m.elems;
    m.elems = nullptr;
}

Matrix::Matrix(const std::size_t& N, std::mt19937& genrand)
{
    std::uniform_real_distribution<double> distr(-1.0,+1.0);
    this->N = N;
    this->elems = new double* [N];
    for ( auto i = 0; i < this->N; ++i ) {
        this->elems[i] = new double [N];
        for ( auto j = 0; j < this->N; ++j ) {
            this->elems[i][j] = distr(genrand);
        }
    }
}

Matrix::~Matrix()
{
    if ( this->N != 0 ) {
        for ( auto i = 0; i < N; ++i ) {
            delete [] this->elems[i];
        }
        delete [] elems;
        this->elems = nullptr;
    }
}

Matrix& Matrix::operator= (const Matrix& m)
{
    if ( this == &m ) {
        return *this;
    } else {
        this->N = m.N;
        this->elems = new double* [N];
        for ( auto i = 0; i < this->N; ++i ) {
            this->elems[i] = new double [N];
            for ( auto j = 0; j < this->N; ++j ) {
                this->elems[i][j] = m.elems[i][j];
            }
        }
        return *this;
    }
}

Matrix& Matrix::operator= (Matrix&& m)
{
    if ( this == &m ) {
        return *this;
    } else {
        this->N = std::move(m.N);
        this->elems = m.elems;
        m.elems = nullptr;
        return *this;
    }
}

Matrix& Matrix::operator+= (const Matrix& m)
{
    for ( auto i = 0; i < this->N; ++i ) {
        for ( auto j = 0; j < this->N; ++j ) {
            this->elems[i][j] += m.elems[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-= (const Matrix& m)
{
    for ( auto i = 0; i < this->N; ++i ) {
        for ( auto j = 0; j < this->N; ++j ) {
            this->elems[i][j] -= m.elems[i][j];
        }
    }
    return *this;
}

template<typename Type>
Matrix& Matrix::operator*= (const Type& a)
{
    for ( auto i = 0; i < this->N; ++i ) {
        for ( auto j = 0; j < this->N; ++j ) {
            this->elems[i][j] *= a;
        }
    }
    return *this;
}

template<typename Type>
Matrix& Matrix::operator/= (const Type& a)
{
    constexpr int mult = 10;
    constexpr Type eps = mult * std::numeric_limits<Type>::epsilon();

    for ( auto i = 0; i < this->N; ++i ) {
        for ( auto j = 0; j < this->N; ++j ) {
            this->elems[i][j] /= a + eps;
        }
    }
    return *this;
}

Matrix operator+ (const Matrix& lhs, const Matrix& rhs)
{
    Matrix temp(lhs.N);
    for ( auto i = 0; i < temp.N; ++i ) {
        for ( auto j = 0; j < temp.N; ++j ) {
            temp.elems[i][j] = lhs.elems[i][j] + rhs.elems[i][j];
        }
    }
    return temp;
}

Matrix operator- (const Matrix& lhs, const Matrix& rhs)
{
    Matrix temp(lhs.N);
    for ( auto i = 0; i < temp.N; ++i ) {
        for ( auto j = 0; j < temp.N; ++j ) {
            temp.elems[i][j] = lhs.elems[i][j] - rhs.elems[i][j];
        }
    }
    return temp;
}

void Matrix::display()
{
    std::cout << std::endl;

    for ( auto i = 0; i < this->N; ++i ) {
        for ( auto j = 0; j < this->N; ++j ) {
            std::cout << std::fixed << std::setprecision(3) << this->elems[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}



int main()
{
    constexpr std::size_t N = 5;
    std::mt19937 genr(N);
    Matrix a(N,genr);
    Matrix b(N,genr);
    a.display();
    b.display();
    Matrix c = a+b;
    c.display();
}
