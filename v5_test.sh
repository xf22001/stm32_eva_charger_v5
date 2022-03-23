#!/bin/bash

#================================================================
#   
#   
#   文件名称：v5_test.sh
#   创 建 者：肖飞
#   创建日期：2022年03月03日 星期四 14时11分19秒
#   修改日期：2022年03月03日 星期四 14时18分11秒
#   描    述：
#
#================================================================
function main() {
	while true;do
		echo start channel 0
		/home/xiaofei/data/source/mycode/c/project/probe_tool/out/bin/probe_tool -c 10.42.0.122 -b " 14 0 1" > /dev/null 2>&1
		sleep 20
		echo stop channel 0
		/home/xiaofei/data/source/mycode/c/project/probe_tool/out/bin/probe_tool -c 10.42.0.122 -b " 14 0 2"  > /dev/null 2>&1
		sleep 20
	done
}

main $@
