#pragma once
#include <QObject>
#include <QString>

class CalculatorService : public QObject {
    Q_OBJECT

	public:
		explicit CalculatorService(QObject* parent = nullptr);

		void appendToken(const QString& tok);
		QString expression() const { return m_expression; }

		void clear();
		void backspace();

		QString evaluate();

	signals:
		void expressionChanged(const QString& expr);
		void resultReady(const QString& result);

	private:
		QString m_expression;
};
