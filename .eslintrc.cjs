module.exports = {
	extends: [
		'erb',
		'plugin:@typescript-eslint/recommended',
		'plugin:@typescript-eslint/recommended-requiring-type-checking',
		'plugin:prettier/recommended',
		'plugin:import/recommended',
		'plugin:import/typescript',
	],
	plugins: ['@typescript-eslint', 'import'],
	rules: {
		'@typescript-eslint/no-shadow': 'error',
		'@typescript-eslint/no-unused-vars': 'error',
		'@typescript-eslint/ban-ts-comment': 'off',
		'@typescript-eslint/interface-name-prefix': 'off',
		'@typescript-eslint/explicit-function-return-type': 'off',
		'@typescript-eslint/explicit-module-boundary-types': 'off',
		'@typescript-eslint/no-unsafe-enum-comparison': 'off',
		'@typescript-eslint/no-namespace': 'off',
		'import/extensions': 'off',
		'import/order': [
			'error',
			{
				'newlines-between': 'always',
				groups: [
					'type',
					'builtin',
					'external',
					'internal',
					['parent', 'sibling', 'index'],
				],
				pathGroups: [
					{
						pattern: '@(database|modules|templates|utils|src)/**',
						group: 'internal',
					},
				],
				pathGroupsExcludedImportTypes: ['builtin'],
				alphabetize: {
					order: 'asc',
					caseInsensitive: true,
				},
			},
		],
		// A temporary hack related to IDE not resolving correct package.json
		'import/no-extraneous-dependencies': 'off',
		'import/no-import-module-exports': 'off',
		'import/no-unresolved': 'off',
		'no-shadow': 'off',
		'no-unused-vars': 'off',
		'no-console': 'warn',
		'prettier/prettier': ['error', { endOfLine: 'lf' }],
		'react/react-in-jsx-scope': 'off',
		'react/jsx-filename-extension': 'off',
	},
	parserOptions: {
		ecmaVersion: 2022,
		sourceType: 'module',
		project: './tsconfig.json',
	},
	settings: {
		'import/resolver': {
			// See https://github.com/benmosher/eslint-plugin-import/issues/1396#issuecomment-575727774 for line below
			node: {},
			webpack: {
				config: require.resolve('./.erb/configs/webpack.config.eslint.ts'),
			},
			typescript: {},
		},
		'import/parsers': {
			'@typescript-eslint/parser': ['.ts', '.tsx'],
		},
	},
};
