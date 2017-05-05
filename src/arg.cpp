#include "utvl/arg.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


#define STR_TO_INT(X) (       atoi((X).c_str()))
#define STR_TO_FLT(X) ((float)atof((X).c_str()))
#define STR_TO_DBL(X) (       atof((X).c_str()))

#define STR_TO_BOOL(X) (((X) == "t" || (X) == "true" || (X) == "on" || (X) == "enable") ? true : false)

template <typename T>
std::string to_str(const T& t)
{
	std::ostringstream os;
	os << t;

	return os.str();
}

#define INT_TO_STR(X) (to_str<int>   ((X)))
#define FLT_TO_STR(X) (to_str<float> ((X)))
#define DBL_TO_STR(X) (to_str<double>((X)))

#define BOOL_TO_STR(X) ((X) ? "true" : "false")

#define DEFAULT_TAG " "


// 前後の空白を除去する
static const std::string STR_REMOVE_BLANK(const std::string &str)
{
	std::string res(str);

	while (0<res.size() && res[0] == ' ')
		res = res.substr(1, res.size()-1);

	while (0<res.size() && res[res.size()-1] == ' ')
		res = res.substr(0, res.size()-1);

	return res;
}


// 区切り文字で分割する
static const std::vector<std::string> STR_SPLIT(const std::string &str)
{
	std::vector<std::string> res;

	std::string temp(str);

	int at = -1;
	while ( (at = (int)(temp.find_first_of('|'))) != temp.npos )
	{
		// 要素があれば獲得
		if (at > 0)
			res.push_back (STR_REMOVE_BLANK(temp.substr(0, at)));

		// 更新
		temp = temp.substr(at + 1);
	}

	// まだ最後に要素が残っていたら獲得
	if (temp.length() > 0)
		res.push_back(STR_REMOVE_BLANK(temp));

	return res;
}


static const std::vector<int> STR_SEARCH(const std::string &str,
	const std::vector<std::string> &str_vec)
{
	std::vector<int> res;

	for (unsigned int i=0; i<str_vec.size(); i++)
	{
		std::vector<std::string> temp = STR_SPLIT(str);
		for (unsigned int j=0; j<temp.size(); j++)
		{
			if (temp[j] == str_vec[i])
			{
				res.push_back(i);
			}
		}
	}

	return res;
}


namespace utvl
{

	
namespace arg
{


Argument::Argument (int argc, char **argv)
{
	for (int i=1; i<argc; i++)
		mArgument += std::string(argv[i]);

#if 0
	std::cout << mArgument << std::endl;
#endif

	parse (mArgument);
}


Argument::~Argument (void)
{
	;
}


const std::string Argument::get (
	const std::string &name, const std::string &default_value)
{
	// 既に獲得済みの argument で name に該当するものがあるかどうかを検索
	std::vector<int> temp = STR_SEARCH(name, mName);

	if (!temp.empty()) // 最終的に見つかった場合
	{
		return mValue[temp[0]];
	}
	else // 最終的に見つからなかった場合 default_value を使用
	{
		mName.push_back(name);
		mValue.push_back(default_value);
		mTag.push_back(DEFAULT_TAG);

		return default_value;
	}
}


const std::vector<std::string> Argument::get (
	const std::string &name, const std::vector<std::string> &default_value)
{
	// 既に獲得済みの argument で name に該当するものがあるかどうかを検索
	std::vector<int> temp = STR_SEARCH(name, mName);

	if (!temp.empty()) // 最終的に見つかった場合
	{
		std::vector<std::string> res;
		for (unsigned int i=0; i<temp.size(); i++)
			res.push_back(mValue[temp[i]]);

		return res;
	}
	else // 最終的に見つからなかった場合 default_value を使用
	{
		for (unsigned int i=0; i<default_value.size(); i++)
		{
			mName.push_back(name);
			mValue.push_back(default_value[i]);
			mTag.push_back(DEFAULT_TAG);
		}

		return default_value;
	}
}


const int Argument::get (
	const std::string &name, const int &default_value)
{
	// 既に獲得済みの argument で name に該当するものがあるかどうかを検索
	std::vector<int> temp = STR_SEARCH(name, mName);

	if (!temp.empty()) // 最終的に見つかった場合
	{
		return STR_TO_INT(mValue[temp[0]]);
	}
	else // 最終的に見つからなかった場合 default_value を使用
	{
		mName.push_back(name);
		mValue.push_back(INT_TO_STR(default_value));
		mTag.push_back(DEFAULT_TAG);

		return default_value;
	}
}


const std::vector<int> Argument::get (
	const std::string &name, const std::vector<int> &default_value)
{
	// 既に獲得済みの argument で name に該当するものがあるかどうかを検索
	std::vector<int> temp = STR_SEARCH(name, mName);

	if (!temp.empty()) // 最終的に見つかった場合
	{
		std::vector<int> res;
		for (unsigned int i=0; i<temp.size(); i++)
			res.push_back(STR_TO_INT(mValue[temp[i]]));

		return res;
	}
	else // 最終的に見つからなかった場合 default_value を使用
	{
		for (unsigned int i=0; i<default_value.size(); i++)
		{
			mName.push_back(name);
			mValue.push_back(INT_TO_STR(default_value[i]));
			mTag.push_back(DEFAULT_TAG);
		}

		return default_value;
	}
}


const float Argument::get (
	const std::string &name, const float &default_value)
{
	// 既に獲得済みの argument で name に該当するものがあるかどうかを検索
	std::vector<int> temp = STR_SEARCH(name, mName);

	if (!temp.empty()) // 最終的に見つかった場合
	{
		return STR_TO_FLT(mValue[temp[0]]);
	}
	else // 最終的に見つからなかった場合 default_value を使用
	{
		mName.push_back(name);
		mValue.push_back(FLT_TO_STR(default_value));
		mTag.push_back(DEFAULT_TAG);

		return default_value;
	}
}


const std::vector<float> Argument::get (
	const std::string &name, const std::vector<float> &default_value)
{
	// 既に獲得済みの argument で name に該当するものがあるかどうかを検索
	std::vector<int> temp = STR_SEARCH(name, mName);

	if (!temp.empty()) // 最終的に見つかった場合
	{
		std::vector<float> res;
		for (unsigned int i=0; i<temp.size(); i++)
			res.push_back(STR_TO_FLT(mValue[temp[i]]));

		return res;
	}
	else // 最終的に見つからなかった場合 default_value を使用
	{
		for (unsigned int i=0; i<default_value.size(); i++)
		{
			mName.push_back(name);
			mValue.push_back(FLT_TO_STR(default_value[i]));
			mTag.push_back(DEFAULT_TAG);
		}

		return default_value;
	}
}


const double Argument::get (
	const std::string &name, const double &default_value)
{
	// 既に獲得済みの argument で name に該当するものがあるかどうかを検索
	std::vector<int> temp = STR_SEARCH(name, mName);

	if (!temp.empty()) // 最終的に見つかった場合
	{
		return STR_TO_DBL(mValue[temp[0]]);
	}
	else // 最終的に見つからなかった場合 default_value を使用
	{
		mName.push_back(name);
		mValue.push_back(DBL_TO_STR(default_value));
		mTag.push_back(DEFAULT_TAG);

		return default_value;
	}
}


const std::vector<double> Argument::get (
	const std::string &name, const std::vector<double> &default_value)
{
	// 既に獲得済みの argument で name に該当するものがあるかどうかを検索
	std::vector<int> temp = STR_SEARCH(name, mName);

	if (!temp.empty()) // 最終的に見つかった場合
	{
		std::vector<double> res;
		for (unsigned int i=0; i<temp.size(); i++)
			res.push_back(STR_TO_DBL(mValue[temp[i]]));

		return res;
	}
	else // 最終的に見つからなかった場合 default_value を使用
	{
		for (unsigned int i=0; i<default_value.size(); i++)
		{
			mName.push_back(name);
			mValue.push_back(DBL_TO_STR(default_value[i]));
			mTag.push_back(DEFAULT_TAG);
		}

		return default_value;
	}
}


const bool Argument::get (
	const std::string &name, const bool &default_value)
{
	// 既に獲得済みの argument で name に該当するものがあるかどうかを検索
	std::vector<int> temp = STR_SEARCH(name, mName);

	if (!temp.empty()) // 最終的に見つかった場合
	{
		return STR_TO_BOOL(mValue[temp[0]]);
	}
	else // 最終的に見つからなかった場合 default_value を使用
	{
		mName.push_back(name);
		mValue.push_back(BOOL_TO_STR(default_value));
		mTag.push_back(DEFAULT_TAG);

		return default_value;
	}
}


const std::vector<bool> Argument::get (
	const std::string &name, const std::vector<bool> &default_value)
{
	// 既に獲得済みの argument で name に該当するものがあるかどうかを検索
	std::vector<int> temp = STR_SEARCH(name, mName);

	if (!temp.empty()) // 最終的に見つかった場合
	{
		std::vector<bool> res;
		for (unsigned int i=0; i<temp.size(); i++)
			res.push_back(STR_TO_BOOL(mValue[temp[i]]));

		return res;
	}
	else // 最終的に見つからなかった場合 default_value を使用
	{
		for (unsigned int i=0; i<default_value.size(); i++)
		{
			mName.push_back(name);
			mValue.push_back(BOOL_TO_STR(default_value[i]));
			mTag.push_back(DEFAULT_TAG);
		}

		return default_value;
	}
}


void Argument::load (const std::string &filename)
{
	std::ifstream in(filename.c_str());

	if (!in)
	{
		;
	}
	else
	{
		std::string argument;

		while (!in.eof())
		{
			std::string line;
			std::getline(in, line);

			// '#'で始まる行は無視して
			// ファイルからの全入力を1行にまとめる
			if (0 < line.size() && line[0] != '#')
				argument += line;
		}

		// 内容を解析する
		parse (argument);

		in.close();
	}
}


void Argument::save (const std::string &filename)
{
	std::ofstream out(filename.c_str());

	if (!out)
	{
		;
	}
	else
	{
		for (unsigned int i=0; i<mName.size(); i++)
			out << mName[i] << " : " << mValue[i] << ";"<< std::endl;

		out.close();
	}
}


void Argument::print (void)
{
#if 1
	// 昇順に並べ替えて表示するための処理
	std::vector<std::pair<std::string, int>> temp;
	for (unsigned int i=0; i<mName.size(); i++)
		temp.push_back(std::pair<std::string, int> (mName[i], i));

	std::sort(temp.begin(), temp.end());
#endif

	size_t name_max = 4;
	for (unsigned int i=0; i<mName.size(); i++)
		name_max = std::max<size_t>(name_max, mName[i].size());

	size_t value_max = 5;
	for (unsigned int i=0; i<mValue.size(); i++)
		value_max = std::max<size_t>(value_max, mValue[i].size());

	for (unsigned int i=0; i<mName.size() + 1; i++)
	{
		const std::string tag = i==0 ? " " : mTag[temp[i-1].second];
		const std::string name = i==0 ? "NAME" : mName[temp[i-1].second];
		const std::string value = i==0 ? "VALUE" : mValue[temp[i-1].second];

		std::cout << " | " << tag << " | " << name;
		
		for (unsigned int j=0; j<name_max - name.size(); j++)
			std::cout << " ";

		std::cout << " | ";

		std::cout << value;
		
		for (unsigned int j=0; j<value_max - value.size(); j++)
			std::cout << " ";
		
		std::cout << " | " << std::endl;
	}
}


void Argument::parse (const std::string &arg)
{
	// ここでの arg は改行が除かれて1行になっている想定
	std::string argment(arg);

	size_t pos;

	while ((pos = argment.find_first_of(";")) != std::string::npos)
	{
		std::string a(argment.substr(0, pos));

		size_t p;

		if ((p = a.find_first_of(":")) != std::string::npos || (p = a.find_first_of("=")) != std::string::npos)
		{
			std::string name = a.substr(0, p);

			std::string value = (p+1 < a.size()) ? a.substr(p+1, a.size() - (p+1)) : "";

			while (0<name.size() && name[name.size()-1] == ' ')
				name = name.substr(0, name.size()-1);

			while (0<value.size() && value[0] == ' ')
				value = value.substr(1, value.size()-1);

			if (0 < value.size() && value[0] != '#')
			{
				mName.push_back(name);
				mValue.push_back(value);
				mTag.push_back("*");

				if (name == "load")
				{
					load (value);
				}
			}
		}

		argment = argment.substr(pos+1);
	}
}


} // namespace arg


} // namespace utvl

