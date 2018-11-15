// https://leetcode.com/problems/basic-calculator
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(N)
class Solution {
private:
    vector<string> toRPN(string &s) {
        vector<string> rpn;
        stack<char> ops;
        for (auto it = s.begin(); it != s.end();) {
            while (it != s.end() && isspace(*it)) ++it;
            if (it == s.end()) break;
            if (isdigit(*it)) {
                string num;
                while (it != s.end() && isdigit(*it)) {
                    num += *it;
                    ++it;
                }
                rpn.push_back(num);
            } else {
                switch(*it) {
                    case '+':
                    case '-':
                        if (ops.size() && ops.top() != '(') {
                            rpn.push_back(string(1, ops.top()));
                            ops.pop();
                        }
                        // fall through
                    case '(':
                        ops.push(*it);
                        break;
                    case ')': 
                        while (ops.top() != '(') {
                            rpn.push_back(string(1, ops.top()));
                            ops.pop();
                        }
                        ops.pop();
                        break;
                }
                ++it;
            }
        }
        while (ops.size()) {
            rpn.push_back(string(1, ops.top()));
            ops.pop();
        }
        return rpn;
    }
    int calcRPN(vector<string> rpn) {
        stack<int> s;
        for (auto &str : rpn) {
            if (isdigit(str[0])) {
                s.push(stoi(str));
            } else {
                int num = s.top();
                s.pop();
                switch(str[0]) {
                    case '+': s.top() += num; break;
                    case '-': s.top() -= num; break;
                }
            }
        }
        return s.top();
    }
public:
    int calculate(string s) {
        return calcRPN(toRPN(s));
    }
};