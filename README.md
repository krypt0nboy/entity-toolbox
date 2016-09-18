# Entity toolbox

### Summary
This module allows to easily create and manage entity types.

### Requirements
* entity
* views
* views_ui
* ctools
* entityreference
* inline_entity_form
* entity_operations

### Installation
Install as usual, see http://drupal.org/node/895232 for further information.

### Configuration
##### Settings
The settings are available at "admin/config/entity_toolbox/settings".

Available settings are :

* Cache enabled
* AJAX enabled
* Notifications enabled

### Basics
##### Entity groups
Entity groups are containers for several types of related entities.
To declare a new group, implement hook_entity_group_info(). 
##### Entities
To declare a new entity type, use hook_entity_toolbox_info().
###### Properties
###### Entity operations

### Usage
##### Creating entity group and entity modules.

1. Create a container module :
    * example_module.info
    * example_module.module
    * example_module.info.inc
    * example_module.functions.inc
    * /src
        * /classes
            * /controllers
                * ExampleGroupController.inc
            * /groups
                * ExampleGroup.inc
2. Within the same module, add a directory named "entities" and create a module for each entity type you wish to add :
    * /entities
        * /foo
            * foo.info
            * foo.install
            * foo.module
            * foo.info.inc
            * foo.functions.inc
            * /src
                * /classes
                    * /controllers
                        * FooController.inc
                        * FooTypeController.inc
                    * /entities
                        * Foo.inc
                        * FooType.inc
                * /templates
                    foo.tpl.php
                    
##### Implementing the hooks
###### .info.inc file
If the module manages an entity group, implement the following.

```
/**
 * Implements hook_entity_group_info().
 */
function entity_toolbox_example_entity_group_info() {
  $info            = array();
  $info['example'] = array(
    'label'       => t('Example'),
    'description' => t('Example entities.'),
    'path'        => 'admin/example',
    'classes'     => array(
      'group'      => 'ExampleGroup',
      'controller' => 'ExampleGroupController'
    ),
  );

  return $info;
}
```
If the module manages an entity type, implement the following.
```
/**
 * Implements hook_entity_toolbox_info().
 */
function foo_entity_toolbox_info() {
  $info             = array();
  $info['foo']      = array(
    'fieldable' => TRUE,
    'group'     => 'example',
  );
  $info['foo_type'] = array(
    'fieldable' => FALSE,
    'group'     => 'example',
  );

  return $info;
}
```
###### .module file
```
/**
 * Implements hook_menu().
 */
function foo_menu() {
  $items = array();
  $items += menu_build('foo');

  return $items;
}

/**
 * Implements hook_entity_info().
 */
function foo_entity_info() {
  $info = array();

  $info += entity_info_retrieve('foo');
  $info += entity_info_retrieve('foo_type');


  return $info;
}

/**
 * Implements hook_entity_property_info().
 */
function foo_entity_property_info() {
  $info = array();
  $info += entity_property_info_build('foo');
  $info += entity_property_info_build('foo_type');

  return $info;
}

/**
 * Implements hook_entity_operation_info().
 */
function foo_entity_operation_info() {
  $info = array();
  $info += entity_operation_info_build('foo');
  $info += entity_operation_info_build('foo_type');

  return $info;
}

/**
 * Implements hook_permission().
 */
function foo_permission() {
  $permissions = array();
  $permissions += permissions_build('foo');
  $permissions += permissions_build('foo_type');

  return $permissions;
}

/**
 * Implements hook_theme().
 */
function foo_theme($existing, $type, $theme, $path) {
  $themes = array();
  $themes += theme_build('foo');

  return $themes;
}
```
###### .install file
```
/**
 * Implements hook_schema().
 */
function foo_schema() {
  $schema = array();
  $schema += schema_build('foo');
  $schema += schema_build('foo_type');

  return $schema;
}

/**
 * Implements hook_uninstall().
 */
function foo_uninstall() {
  entity_toolbox_uninstall('foo');
}
```
###### TODO

- [ ] 