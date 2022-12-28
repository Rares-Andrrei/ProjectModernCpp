#pragma once
enum class CredentialErrors : int
{
	NameSize,
	UsernameSize,
	PasswordSize,
	UserTaken,
	NameTaken,
	IncorrectAccount,
	IncorrectPassword,
	Valid,
	Other
};