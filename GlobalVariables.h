#pragma once
#include<map>
#include<string>
#include<variant>
#include"Vector3.h"
class GlobalVariables {
public:
	static GlobalVariables* GetInstance();

private:
	GlobalVariables() = default;
	~GlobalVariables() = default;
	GlobalVariables(const GlobalVariables& obj) = delete;
	GlobalVariables& operator=(const GlobalVariables& obj) = delete;

	//項目
	struct Item {
		//項目の値
		std::variant<int32_t, float, Vector3> value;

	};

	//グループ
	struct Group {
		std::map<std::string,Item> items;
	};
	//全データ
	std::map<std::string, Group> datas_;

	public:
		/// <summary>
		/// グループの作成
		/// </summary>
		/// <param name="groupName">グループ名</param>
	    void CreateGroup(const std::string& groupName);
		//値のセット(int)
		void SetValue(const std::string& groupName, const std::string& key, int32_t value);
		//値のセット(float)
	    void SetValue(const std::string& groupName, const std::string& key, float value);
		//値のセット(Vector3)
	    void SetValue(const std::string& groupName, const std::string& key, const Vector3& value);

		/// <summary>
	    /// 更新処理
	    /// </summary>
	    void Update();

};
