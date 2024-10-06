return {
	name: 'University',
	colors: #game.factions.import_colors('univ.pcx'),
	bases: {
		render: {
			type: 'sprite_grid',
			file: 'univ.pcx',
			grid_x: 1, grid_y: 1,
			cell_width: 100, cell_height: 75,
			cell_padding: 1,
		},
		names: #game.factions.import_base_names('univ.txt'),
	},
};
