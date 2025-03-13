// json_stroe.cpp: 定义应用程序的入口点。
//

#include "json_stroe.h"

#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include<string>
#include "pqxx/pqxx"


using namespace std;
using json = nlohmann::json;

using namespace pqxx;


 string DB_CONN_STR = "host=140.143.151.197 port=5432 dbname=postgres user=postgres password=19961105wjt";
string readfile(const string & filename){
	ifstream  file(filename);
	if (!file.is_open()) {
		throw runtime_error("failed to open file :" +filename);
	}
	stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();


}

//解析json文件
json parse_json(const string& filename) {
	string content = readfile(filename);
	json data = json::parse(content);

	if (!data.is_object()) {
		throw runtime_error("Invalid json format: expected  an array");
	}
	return data;

	
}

//插入数据
void insert_data_to_postgresql(const json& data) {
	connection conn(DB_CONN_STR);
	pqxx::work txn(conn);
	string sql = "INSERT INTO sta_hikvision_info "
		"(regionindex_code,channel_no,latitude, channel_type,update_time, cameraindex_code, gbindex_code, camera_type, trans_type, create_time, camera_type_name, capability_set, encode_dev_index_code, channel_type_name, trans_type_name, camera_name,longitude) "
		"VALUES";
	string* sqls = new string("INSERT INTO S");
	sqls->size();
	sqls->length();
	delete sqls;
	json field = data["list"];
	json re = field[0];
	for (auto& item : field) {

		cout <<endl<< sql<<endl<<endl<< sql.size()<< endl;
		sql += "(";
		if (item.contains("regionIndexCode") && !item["regionIndexCode"].is_null()) {
			sql += txn.quote(item["regionIndexCode"].get<string>()) + ",";
		}
		else {
			
			sql += "null,";
		}

		if (item.contains("channelNo") && !item["channelNo"].is_null()) {
			sql += txn.quote(item["channelNo"].get<string>())+",";
		}
		else {
			sql += "null,";
		}

		if (item.contains("latitude") && !item["latitude"].is_null())
		{
			sql += txn.quote(item["latitude"].get<string>()) + ",";
		}
		else {
			sql += "null,";
		}

		if (item.contains("channelType") && !item["channelType"].is_null())
		{
			sql += txn.quote(item["channelType"].get<string>()) + ",";
		}
		else {
			sql += "null,";
		}

		if (item.contains("updateTime") && !item["updateTime"].is_null())
		{
			sql += txn.quote(item["updateTime"].get<string>()) + ",";
		}
		else {
			sql += "null,";
		}

		if (item.contains("cameraIndexCode") && !item["cameraIndexCode"].is_null())
		{
			sql += txn.quote(item["cameraIndexCode"].get<string>()) + ",";
		}
		else {
			sql += "null,";
		}

		if (item.contains("gbIndexCode") && !item["gbIndexCode"].is_null())
		{
			sql += txn.quote(item["gbIndexCode"].get<string>()) + ",";
		}
		else {
			sql += "null,";
		}

		if (item.contains("cameraType") && !item["cameraType"].is_null())
		{
			sql += txn.quote(item["cameraType"].get<int>()) + ",";
		}
		else {
			sql += ",";
		}

		if (item.contains("transType") && !item["transType"].is_null())
		{
			sql += txn.quote(item["transType"].get<int>()) + ",";
		}
		else {
			sql += "null,";
		}

		if (item.contains("createTime") && !item["createTime"].is_null())
		{
			sql += txn.quote(item["createTime"].get<string>()) + ",";
		}
		else {
			sql += "null,";
		}

		if (item.contains("cameraTypeName") && !item["cameraTypeName"].is_null())
		{
			sql += txn.quote(item["cameraTypeName"].get<string>()) + ",";
		}
		else {
			sql += "null,";
		}

		if (item.contains("capabilitySet") && !item["capabilitySet"].is_null())
		{
			sql += txn.quote(item["capabilitySet"].get<string>()) + ",";
		}
		else {
			sql += "null,";
		}

		if (item.contains("encodeDevIndexCode") && !item["encodeDevIndexCode"].is_null())
		{
			sql += txn.quote(item["encodeDevIndexCode"].get<string>()) + ",";
		}
		else {
			sql += "null,";
		}

		if (item.contains("channelTypeName") && !item["channelTypeName"].is_null())
		{
			sql += txn.quote(item["channelTypeName"].get<string>()) + ",";
		}
		else {
			sql += "null,";
		}

		if (item.contains("transTypeName") && !item["transTypeName"].is_null())
		{
			sql += txn.quote(item["transTypeName"].get<string>()) + ",";
		}
		else {
			sql += "null,";
		}

		if (item.contains("cameraName") && !item["cameraName"].is_null())
		{
			sql += txn.quote(item["cameraName"].get<string>()) + ",";
		}
		else {
			sql += "null,";
		}

		if (item.contains("longitude") && !item["longitude"].is_null())
		{
			sql += txn.quote(item["longitude"].get<string>()) + "),";
		}
		else {
			sql += "null),";
		}


		

	}
	sql.erase(sql.end()-1);
	cout << endl <<"sql:::::--- " << sql << endl;
	try {
		txn.exec_params(sql);
	}
	catch (const runtime_error& e) {
		std::cerr << "SQL Syntax Error " << e.what() << endl;
	}

	txn.commit();
	
}


int main()
{
	const string filename = "C:\\Users\\83520\\Desktop\\11baa59c-7b1f-467d-9a00-35e4c5dcd634.json";
	json objects = parse_json(filename);
	json datas = objects["data"];
	insert_data_to_postgresql(datas);
	cout << datas << endl<<endl;
	system("pause");
}
