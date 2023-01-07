// built-in include guard removal
// just in case the user has a local dependency with the same file name
#if defined _inc_samp_money
    #undef _inc_samp_money
#endif

// custom include-guard to ensure we don't duplicate
#if defined _samp_money_included
	#endinput
#endif
#define _samp_money_included

#include <open.mp>

static 
	INC_gsMoney[MAX_PLAYERS];

public OnPlayerUpdate(playerid)
{
	new
		money = GetPlayerMoney(playerid);
	if(money != INC_gsMoney[playerid])
	{
		if(money > INC_gsMoney[playerid])
		{
			ResetPlayerMoney(playerid);
			GivePlayerMoney(playerid, INC_gsMoney[playerid]);
		}
		else
		{
			INC_gsMoney[playerid] = money;
		}
	}
	#if defined Money_OnPlayerUpdate
		return Money_OnPlayerUpdate(playerid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate Money_OnPlayerUpdate
#if defined Money_OnPlayerUpdate
	forward Money_OnPlayerUpdate(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	INC_gsMoney[playerid] = 0;
	#if defined Money_OnPlayerDisconnect
		return Money_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect Money_OnPlayerDisconnect
#if defined Money_OnPlayerDisconnect
	forward Money_OnPlayerDisconnect(playerid, reason);
#endif

stock Money_ResetPlayerMoney(playerid)
{
	new
		ret = ResetPlayerMoney(playerid);
	if(ret)
	{
		INC_gsMoney[playerid] = 0;
	}

	return ret;
}

#if defined _ALS_ResetPlayerMoney
	#undef ResetPlayerMoney
#else
	#define _ALS_ResetPlayerMoney
#endif
#define ResetPlayerMoney( Money_ResetPlayerMoney(

stock Money_GivePlayerMoney(playerid, money)
{
	new
		ret = GivePlayerMoney(playerid, money);
	if(ret)
	{
		INC_gsMoney[playerid] += money;
	}

	return ret;
}

#if defined _ALS_GivePlayerMoney
	#undef GivePlayerMoney
#else
	#define _ALS_GivePlayerMoney
#endif
#define GivePlayerMoney( Money_GivePlayerMoney(

/**
 * <library>omp-money</library>
 * <summary>Sets money for a player.</summary>
 * <param name="playerid">The ID of the player to set money to</param>
 * <param name="money">The amount of money to set.</param>
 * <seealso name="GivePlayerMoney" />
 * <returns>
 *   <b><c>true</c></b>: The function executed successfully.<p/>
 *   <b><c>false</c></b>: The function failed to execute. This means the player is not connected.
 * </returns>
 */
stock SetPlayerMoney(playerid, money)
{
	new
		ret = ResetPlayerMoney(playerid);
	if(ret)
	{
		GivePlayerMoney(playerid, money);
	}

	return ret;
}