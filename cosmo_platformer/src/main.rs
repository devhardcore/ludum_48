use bevy::{input::system::exit_on_esc_system, prelude::*};

struct Position { x: i32, y: i32 }

struct Champion { value: i32, max_value: i32 }

fn init_world(mut commands: Commands) {
    commands.spawn().insert(Champion).insert(Position(10, 0));
}

fn main() {
    App::build()
        .add_startup_system(init_world.system())
        .insert_resource(WindowDescriptor {
            title: "Zdohni ili umri".to_string(),
            width: 1280.,
            height: 768.,
            ..Default::default()
        })
        .add_plugins(DefaultPlugins)
        .add_system(exit_on_esc_system.system())
        .run();
}