#include "CalculatorService.h"
#include <QtGlobal>
#include <QStack>

CalculatorService::CalculatorService(QObject* parent) : QObject(parent) {}

void CalculatorService::appendToken(const QString& tok) {
    m_expression += tok;
    emit expressionChanged(m_expression);
}

void CalculatorService::clear() {
    m_expression.clear();
    emit expressionChanged(m_expression);
}

void CalculatorService::backspace() {
	if (!m_expression.isEmpty()) {
		m_expression.chop(1);
		emit expressionChanged(m_expression);
	}
}

// Supports + - * / and integers/floats, no parentheses, left->right except * and /
QString CalculatorService::evaluate() {
    if (m_expression.isEmpty()) return QString();

    // Tokenize
    QList<QString> numbers; QList<QChar> ops;
    QString current;
    for (QChar c : m_expression) {
        if (c.isDigit() || c == '.') {
            current += c;
        } else if (QString("+-*/").contains(c)) {
            if (current.isEmpty()) return QStringLiteral("Error");
            numbers << current; current.clear();
            ops << c;
        } else {
            return QStringLiteral("Error");
        }
    }
    if (!current.isEmpty()) numbers << current; else return QStringLiteral("Error");
    if (numbers.isEmpty()) return QString();

    // Convert to doubles
    QList<double> vals; vals.reserve(numbers.size());
    bool ok = true;

	for (auto &n : numbers) {
		double v = n.toDouble(&ok);
		if(!ok) return QStringLiteral("Error");
		vals << v;
	}

    // First pass * /
    QList<double> reducedVals; QList<QChar> reducedOps;
    reducedVals << vals[0];
    for (int i = 0; i < ops.size(); ++i) {
        QChar op = ops[i];
        double rhs = vals[i + 1];
        if (op == '*' || op == '/') {
            double lhs = reducedVals.takeLast();
            if (op == '*') reducedVals << (lhs * rhs); else {
                if (rhs == 0.0)
					return QStringLiteral("Error");
                reducedVals << (lhs / rhs);
            }
        } else reducedVals << rhs; reducedOps << op;
    }

    // Second pass + -
    double acc = reducedVals[0];
    for (int i = 0; i < reducedOps.size(); ++i) {
        QChar op = reducedOps[i];
        double rhs = reducedVals[i + 1];
        if (op == '+') acc += rhs; else acc -= rhs;
    }

    QString result = QString::number(acc);
    emit resultReady(result);
    return result;
}
