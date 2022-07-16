#pragma once
const long long bufSize = 1024 * 10;//10K缓冲区（应该不多）
//初始化日志
void logInit();
//停止日志
void logStop();
//发送日志（务必使用ascii编码）
void sendLog(const char severity, const char content[bufSize - 2]);
#define log_message 1
#define log_warning 2
#define log_error 3
#define log_fatal 4