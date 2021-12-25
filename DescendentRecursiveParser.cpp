#include "DescendentRecursiveParser.h"
#include <iostream>

string DescendentRecursiveParser::stack_toString(stack<string> stk)
{
    string res = "";
    while (!stk.empty())
    {
        res += stk.top();
        stk.pop();
    }
    return res;
}

string DescendentRecursiveParser::vector_toString(vector<string> vct)
{
    string res = "";
    for (auto e : vct)
        res += e;
    return res;
}

string DescendentRecursiveParser::state_toString(State state)
{
    if (state == State::NORMAL)
        return "q";
    if (state == State::BACK)
        return "b";
    if (state == State::FINAL)
        return "f";
    if (state == State::ERROR)
        return "e";
    return "";
}

bool DescendentRecursiveParser::isNonTerminal(string e)
{
    return e >= "A" && e <= "Z";
}

void DescendentRecursiveParser::details()
{
    cout << "("
         << this->state_toString(this->state) << ", "
         << this->i << ", "
         << vector_toString(this->working_stack) << ", "
         << stack_toString(this->input_stack) << ")\n";
}

DescendentRecursiveParser::DescendentRecursiveParser(Grammar grammar)
{
    this->grammar = &grammar;
    this->state = State::NORMAL;
    this->i = 1;
    this->working_stack = vector<string>();
    this->input_stack = stack<string>();
    this->input_stack.push(grammar.get_Start_Symbol());

    for (auto rule : this->grammar->get_Transformations())
        this->rules[rule.first].push_back(make_pair(rule.first, rule.second));

    for (auto &rule : this->rules)
        for (int i = 0; i < rule.second.size(); i++)
            rule.second[i].first += char(i + '1');
}

void DescendentRecursiveParser::Success()
{
    this->state = State::FINAL;
}

void DescendentRecursiveParser::Expand()
{
    string nonTerminal = this->input_stack.top();
    this->input_stack.pop();

    auto rule = this->rules[nonTerminal].front();
    for (int i = rule.second.size() - 1; i >= 0; i--)
        this->input_stack.push(string(1, rule.second[i]));

    this->working_stack.push_back(rule.first);
}

void DescendentRecursiveParser::Advance()
{
    this->i++;
    string terminal = this->input_stack.top();
    this->input_stack.pop();
    this->working_stack.push_back(terminal);
}

void DescendentRecursiveParser::MomentaryInsuccess()
{
    this->state = State::BACK;
}

void DescendentRecursiveParser::Back()
{
    this->i--;
    string terminal = this->working_stack.back();
    this->working_stack.pop_back();
    this->input_stack.push(terminal);
}

void DescendentRecursiveParser::AnotherTry()
{
    string lastRule = this->working_stack.back();
    string nonTerminal = string(1, lastRule[0]);

    pair<string, string> nextRule;
    for (int i = 0; i < this->rules[nonTerminal].size(); i++)
    {
        if (this->rules[nonTerminal][i].first == lastRule)
        {
            string right = this->rules[nonTerminal][i].second;

            this->working_stack.pop_back();
            for (int i = 0; i < right.size(); i++)
            {
                if (this->input_stack.top()[0] == right[i])
                    this->input_stack.pop();
            }

            if (i < this->rules[nonTerminal].size() - 1)
            {
                nextRule = this->rules[nonTerminal][i + 1];
                this->state = State::NORMAL;
                this->working_stack.push_back(nextRule.first);
                for (int i = nextRule.second.size() - 1; i >= 0; i--)
                    this->input_stack.push(string(1, nextRule.second[i]));
                return;
            }
            else
            {
                this->input_stack.push(nonTerminal);
                // can't back anymore -> error
                if (this->i == 1 && nonTerminal == this->grammar->get_Start_Symbol())
                {
                    this->state = State::ERROR;
                    return;
                }

                // back deeper
                return;
            }
        }
    }
}

void DescendentRecursiveParser::BuildStringOfProd(vector<string> stk)
{

}

///////////// TEST
void DescendentRecursiveParser::test()
{
    // for (auto rule : this->rules)
    // {
    //     cout << rule.first << ":\n";
    //     for (int i = 0; i < rule.second.size(); i++)
    //         cout << "   " << rule.second[i].first << " -> " << rule.second[i].second << endl;
    // }

    this->details();

    this->Expand();
    this->details();

    this->Advance();
    this->details();

    this->Expand();
    this->details();

    this->MomentaryInsuccess();
    this->details();

    this->AnotherTry();
    this->details();

    this->Advance();
    this->details();

    this->Advance();
    this->details();

    this->Success();
    this->details();
}

void DescendentRecursiveParser::parse(string word)
{
    int n = word.length();
    word = " " + word;
    cout << "w:" << word << endl;

    while (true)
    {
        this->details();

        if (this->state == State::NORMAL) // ---------- NORMAL ------------
        {
            if (i == n + 1 && this->input_stack.empty())
            {
                cout << "Success:\n";
                this->Success();
            }
            else if (this->isNonTerminal(this->input_stack.top()))
            {
                cout << "Expand:\n";
                this->Expand();
            }
            else if (this->input_stack.top() == string(1, word[i]))
            {
                cout << "Advance:\n";
                this->Advance();
            }
            else
            {
                cout << "Mom. Insuccess:\n";
                this->MomentaryInsuccess();
            }
        }

        else if (this->state == State::BACK) // ---------- BACK ------------
        {
            if (!this->isNonTerminal(this->working_stack.back()))
            {
                cout << "Back:\n";
                this->Back();
            }
            else
            {
                cout << "AnotherTry:\n";
                this->AnotherTry();
            }
        }

        else if (this->state == State::ERROR) // ---------- ERROR ------------
        {
            cout << "Error\n";
            return;
        }

        else if (this->state == State::FINAL) // ---------- FINAL ------------
        {
            cout << "Sequence Accepted!\n";
            this->BuildStringOfProd(this->working_stack);
            return;
        }
    }
}