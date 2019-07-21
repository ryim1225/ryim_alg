#ifndef _R_EXCEPTION_H_
#define _R_EXCEPTION_H_
namespace Ryim
{
	class BaseException
	{
	public:
		BaseException():strExceptionMessage(NULL){}
		explicit BaseException(char* message) :strExceptionMessage(message)
		{
			unId = 0;
		}
		~BaseException() {}
		unsigned int id() const { return unId; }
		char* errorMessage() const {return strExceptionMessage;}
	protected:
		char* strExceptionMessage;
		unsigned int unId;
	};

	class illegalParameterValue: public BaseException
	{
	public:
		explicit illegalParameterValue(char* message) : BaseException(message)
		{
			unId = 1;
		}
		~illegalParameterValue() {}
	};

	class illegalIndex : public BaseException
	{
	public:
		illegalIndex(char* message) : BaseException(message)
		{
			unId = 2;
		}
		~illegalIndex() {}
	};

	class illegalIterator: public BaseException
	{
	public:
		illegalIterator(char* message) : BaseException(message)
		{
			unId = 3;
		}
		~illegalIterator() {}
	};
}
#endif
