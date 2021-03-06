/*!
 * \file PyCtaContext.cpp
 * \project	WonderTrader
 *
 * \author Wesley
 * \date 2020/03/30
 * 
 * \brief 
 */
#include "PyCtaContext.h"
#include "WtRtRunner.h"

#include "../Share/StrUtil.hpp"

extern WtRtRunner& getRunner();

PyCtaContext::PyCtaContext(WtCtaEngine* env, const char* name)
	: CtaStraBaseCtx(env, name)
{
}


PyCtaContext::~PyCtaContext()
{
}

void PyCtaContext::on_init()
{
	CtaStraBaseCtx::on_init();

	//向外部回调
	getRunner().ctx_on_init(_context_id);
}

void PyCtaContext::on_session_begin()
{
	CtaStraBaseCtx::on_session_begin();
}

void PyCtaContext::on_session_end()
{
	CtaStraBaseCtx::on_session_end();
}

void PyCtaContext::on_tick_updated(const char* stdCode, WTSTickData* newTick)
{
	getRunner().ctx_on_tick(_context_id, stdCode, newTick);
}

void PyCtaContext::on_bar_close(const char* stdCode, const char* period, WTSBarStruct* newBar)
{
	//要向外部回调
	getRunner().ctx_on_bar(_context_id, stdCode, period, newBar);
}

void PyCtaContext::on_mainkline_updated(uint32_t curDate, uint32_t curTime)
{
	getRunner().ctx_on_calc(_context_id);
}
