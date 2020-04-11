#include <iostream>
#include <math.h>
using namespace std;

const int MAX_YEARS = 30;
const double YEAR_RATE = 0.0325; // 年利率3.25%
const double MONTH_RATE = YEAR_RATE / 12.0; // 月利率

/* 用途：计算确定贷款额度和贷款时间情况下，等额本息的还款情况
 * input：总本金，贷款总月数
 * output: 等额本息月还款额，每月包含的本金和利息
 */
void calc(double all_loan, int loan_months)
{
    // 等额本息还款法: 每月月供额=〔贷款本金×月利率×(1＋月利率)＾还款月数〕÷〔(1＋月利率)＾还款月数-1〕
    // 月还款额分母
    double de = pow(1 + MONTH_RATE, loan_months) - 1;
    // 月还款额分子
    double me = all_loan * MONTH_RATE * pow(1 + MONTH_RATE, loan_months);
    double month_pay = me / de;
    //cout << "等额本息月还款额：" << month_pay << endl;

    // 每月应还利息=贷款本金×月利率×〔(1+月利率)^还款月数-(1+月利率)^(还款月序号-1)〕÷〔(1+月利率)^还款月数-1〕
    // 每月应还本金=贷款本金×月利率×(1+月利率)^(还款月序号-1)÷〔(1+月利率)^还款月数-1〕
    for (int i = 1; i < MAX_YEARS + 1; ++ i) {
        for (int j = 1; j < 12 + 1; ++ j) {
            int index = j + (i - 1) * 12; // 还款月序号
            if (index > loan_months) {
                break;
            }
            double interest = all_loan * MONTH_RATE * (pow(1+MONTH_RATE,loan_months) - pow(1+MONTH_RATE,index-1)) / de;
            double capital = all_loan * MONTH_RATE * pow(1+MONTH_RATE,index-1) / de;
            //cout<<"第"<<i<<"年，第"<<j<<"月, 总第"<<index<<"月，应还本金："<<capital<<", 应还利息："<< interest << endl;
            cout<<i<<"  "<<j<<" "<<index<<" "<<month_pay<<" "<<capital<<"   "<<interest<<endl;
        }
    }    

    // 总利息=还款月数×每月月供额-贷款本金
    double all_pay = (loan_months * month_pay) / 10000;
    double all_interest = all_pay - all_loan / 10000;
    cout << "总还款额：" << all_pay << "万，总本金：" << all_loan / 10000<< "万, 总利息：" << all_interest << "万" <<endl;
}

void calc_with_min(double origin_all_loan, double all_loan, int loan_months, double min_month_pay, int index)
{
    static double all_interest = 0;
    static double all_loan_tmp = 0;
    if (loan_months <= 0) {
        // 总利息=还款月数×每月月供额-贷款本金
        double all_pay = origin_all_loan + all_interest;
        cout << "总还款额：" << all_pay/10000.0 << "万，总本金：" << origin_all_loan/10000.0<< "万, 总利息：" << all_interest/10000.0 << "万" <<endl;
        return;
    }

    // 等额本息还款法: 每月月供额=〔贷款本金×月利率×(1＋月利率)＾还款月数〕÷〔(1＋月利率)＾还款月数-1〕
    // 月还款额分母
    double de = pow(1 + MONTH_RATE, loan_months) - 1;
    // 月还款额分子
    double me = all_loan * MONTH_RATE * pow(1 + MONTH_RATE, loan_months);
    double month_pay = me / de;
    //cout << "等额本息月还款额：" << month_pay<<" # ";

    double interest = all_loan * MONTH_RATE * (pow(1+MONTH_RATE,loan_months) - pow(1+MONTH_RATE,1-1)) / de;
    all_interest += interest;

    double capital = min_month_pay - interest;
    if (loan_months == 1) {
        capital = origin_all_loan*1.0 - all_loan_tmp;
    }
    all_loan_tmp += capital;

    int i = (index-1) / 12 + 1;
    int j = (index-1) % 12 + 1;
    //cout<<"第"<<i<<"年，第"<<j<<"月, 总第"<<index<<"月，应还本金："<<capital<<", 应还利息："<< interest << endl;
    cout<<i<<"  "<<j<<" "<<index<<" "<<month_pay<<" "<<capital<<"   "<< interest<<endl;

    all_loan = all_loan - capital;
    loan_months --;
    index++;
    calc_with_min(origin_all_loan, all_loan, loan_months, min_month_pay, index);
}

int main()
{
    // 正常还款流程
    double all_loan = 1200000; // 公积金贷款总额120万
    //int loan_years = 23; // 贷款23年
    int loan_years = 25; // 贷款23年
    int loan_months = loan_years * 12; // 贷款月数
    //calc(all_loan, loan_months);

    // 使用最低还款额后的还款流程
    //double min_month_pay = 5019;
    double min_month_pay = 4921;
    //calc_with_min(all_loan, all_loan, loan_months, min_month_pay, 1);
    
    double cur_all_loan = all_loan - 25545.81;
    int cur_loan_months = 25*12 - 15;
    calc(cur_all_loan, cur_loan_months);
    

    return 0;
}

