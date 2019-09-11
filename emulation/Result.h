//
// Created by Revolware Company on 2019-09-07.
//

#ifndef XGBE_RESULT_H
#define XGBE_RESULT_H

template<typename ResultType>
class Result {
public:
	Result() = default;
	Result(ResultType &&result) : m_result{result}, m_isValid{true} {}

	ResultType &operator()() { return m_result; }
	const ResultType &operator()() const { return m_result; }
	explicit operator bool() const { return m_isValid; }

private:
	ResultType m_result = {};
	bool m_isValid = false;
};

#endif //XGBE_RESULT_H
