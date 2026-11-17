#include "main.h"

#include <iostream>

// operator[]で武器IDに対応する所持弾数を追加または更新する。
void WeaponInventory::RegisterWeapon(WeaponID weaponId, int bulletCount)
{
	weaponBulletCounts[weaponId] = bulletCount;
}

// findで所持状態と残弾を確認してから、発射できる場合だけ弾を1発消費する。
FireResult WeaponInventory::Fire(WeaponID weaponId)
{
	auto itWeapon = weaponBulletCounts.find(weaponId);
	if (itWeapon == weaponBulletCounts.end())
	{
		return FireResult::WeaponNotOwned;
	}

	if (itWeapon->second < 1)
	{
		return FireResult::OutOfBullets;
	}

	--itWeapon->second;
	return FireResult::Fired;
}

// 範囲for文で全ての武器IDと所持弾数を一覧表示する。
void WeaponInventory::Display(std::ostream& output) const
{
	for (const auto& [weaponId, bulletCount] : weaponBulletCounts)
	{
		output << static_cast<int>(weaponId) << ": " << bulletCount << '\n';
	}
}

int main()
{
	WeaponInventory inventory;
	inventory.RegisterWeapon(WeaponID::RocketLauncher, 5);

	const FireResult fireResult = inventory.Fire(WeaponID::RocketLauncher);
	if (fireResult == FireResult::WeaponNotOwned)
	{
		std::cout << "Weapon not owned\n";
		return 1;
	}

	if (fireResult == FireResult::OutOfBullets)
	{
		std::cout << "Out of bullets\n";
		return 1;
	}

	std::cout << "Fired\n";
	inventory.Display(std::cout);

	return 0;
}
