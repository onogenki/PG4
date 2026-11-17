#pragma once

#include <iosfwd>
#include <map>

enum class WeaponID {
	Handgun = 100,
	SubmachineGun = 300,
	RocketLauncher = 900,
};

enum class FireResult {
	Fired,
	WeaponNotOwned,
	OutOfBullets,
};

class WeaponInventory
{
public:
	// operator[]で武器IDに対応する所持弾数を追加または更新する。
	void RegisterWeapon(WeaponID weaponId, int bulletCount);

	// findで所持状態と残弾を確認してから、発射できる場合だけ弾を1発消費する。
	FireResult Fire(WeaponID weaponId);

	// 範囲for文で所持中の武器IDと残弾を武器IDの昇順で出力する。
	void Display(std::ostream& output) const;

private:
	std::map<WeaponID, int> weaponBulletCounts;
};
