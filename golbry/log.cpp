#ifndef __GOLBRY_LOG_H__
#define __GOLBRY_LOG_H__


#include <string>
#include <stdint.h>
#include <memory>

namespace golbry{
    class LogEvent{
    public:
        LogEvent();
    private:
        const char * m_file= nullptr;   // 文件名
        int32_t m_line=0;               // 行号
        uint32_t m_elapse=0;            // 查询启动开始到现在的毫秒数
        uint32_t m_threadId=0;          // 线程id
        uint32_t m_fiberId=0;           // 协程id
        uint64_t m_time;                // 时间戳
        std::string m_content;
    };

    class LogLevel{
    public:
        enum Level{
            DEBUG=1,
            INFO=2,
            WARN=3,
            ERROR=4,
            FATAL=5
        };
    };

    class LogFormatter{
    public:
        typedef std::shared_ptr<LogFormatter> ptr;
        std::string format(LogEvent::ptr event);
    private:
    };

    // 日志输出地
    class LogAppender{
    public:
        typedef std::shared_ptr<LogAppender> ptr;
        virtual ~LogAppender(){}

        void log(LogLevel::Level level,LogEvent::ptr event);
    private:
        LogLevel::Level m_level;

    };

    // 日志器
    class Logger{
    public:
        Logger(const std::string& name="root");
        void log(LogLevel::Level level,const LogEvent& event);
    private:
        std::string m_name;
        LogLevel::Level m_level;
        LogAppender::ptr;
    };
    // 输出到控制台的Appender
    class StdoutLogAppender:public LogAppender{

    };
    // 定义输出到文件到Appender
    class FileLogAppender : public LogAppender{

    };

}
#endif