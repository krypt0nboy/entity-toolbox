<?php

/**
 * Determines whether the given user has access to a foo.
 *
 * @param string $op
 *   The operation being performed. One of 'view', 'update', 'create', 'delete'
 *   or just 'edit' (being the same as 'create' or 'update').
 * @param object $foo
 *   Optionally a foo or a foo type to check access for.
 *   If nothing is given, access for all foos is determined.
 * @param object $account
 *   The user to check for. Leave it to NULL to check for the global user.
 *
 * @return bool
 *   Whether access is allowed or not.
 */
function foo_access($op, $foo = NULL, $account = NULL) {
  if (user_access('administer foos', $account)) {
    return TRUE;
  }
  if (isset($foo) && $type_name = $foo->type) {
    $op = ($op == 'view') ? 'view' : 'edit';
    if (user_access("$op any $type_name foo", $account)) {
      return TRUE;
    }
  }

  $access = module_invoke_all('foo_access', $op, $foo, $account);
  if (in_array(FALSE, $access, TRUE)) {
    return FALSE;
  }
  elseif (in_array(TRUE, $access, TRUE)) {
    return TRUE;
  }

  return FALSE;
}

/**
 * Access callback for the entity API.
 */
function foo_type_access($op, $type = NULL, $account = NULL) {
  return user_access('administer foo line types', $account);
}

/**
 * Gets an array of all foo types, keyed by the type name.
 *
 * @param string $type_name
 *   If set, the type with the given name is returned.
 *
 * @return FooType[]
 *   Depending whether $type isset, an array of foo types
 *   or a single one.
 */
function foo_get_types($type_name = NULL) {
  // entity_load will get the Entity controller for our foo entity
  // and call the load function of that object - we are loading entities
  // by name here.
  $types = entity_load_multiple_by_name('foo_type', isset($type_name) ? array($type_name) : FALSE);

  return isset($type_name) ? reset($types) : $types;
}

/**
 * Menu argument loader; Load a foo type by string.
 *
 * @param string $type
 *   The machine-readable name of a foo type to load.
 *
 * @return array|bool
 *   A foo type array or FALSE if $type does not exist.
 */
function foo_type_load($type) {
  return foo_get_types($type);
}

/**
 * Fetch a foo object; make sure that the wildcard you choose
 * in the foo entity definition fits the function name here.
 *
 * @param int  $foo_id
 *   Integer specifying the foo id.
 * @param bool $reset
 *   A boolean indicating that the internal cache should be reset.
 *
 * @return object|bool
 *   A fully-loaded $foo object or FALSE if it cannot be loaded.
 *
 * @see foo_load_multiple()
 */
function foo_load($foo_id, $reset = FALSE) {
  $foos = foo_load_multiple(array($foo_id), array(), $reset);

  return reset($foos);
}

/**
 * Load multiple foos based on certain conditions.
 *
 * @param array $foo_ids
 *   An array of foo IDs.
 * @param array $conditions
 *   An array of conditions to match against the {foo} table.
 * @param bool  $reset
 *   A boolean indicating that the internal cache should be reset.
 *
 * @return array
 *   An array of foo objects, indexed by foo_id.
 *
 * @see entity_load()
 * @see foo_load()
 */
function foo_load_multiple($foo_ids = array(), $conditions = array(), $reset = FALSE) {
  return entity_load('foo', $foo_ids, $conditions, $reset);
}

/**
 * Deletes a foo.
 *
 * @param \Foo $foo
 *   Entity foos.
 */
function foo_delete(Foo $foo) {
  $foo->delete();
}

/**
 * Delete multiple foos.
 *
 * @param array $foo_ids
 *   An array of foo IDs.
 */
function foo_delete_multiple(array $foo_ids) {
  entity_get_controller('foo')->delete($foo_ids);
}

/**
 * Create a foo object.
 *
 * @param array $values
 *   An array of values.
 */
function foo_create($values = array()) {
  return entity_get_controller('foo')->create($values);
}

/**
 * Saves a foo to the database.
 *
 * @param \Foo $foo
 *   The foo object.
 */
function foo_save(Foo $foo) {
  return $foo->save();
}

/**
 * Saves a foo type to the db.
 *
 * @param \FooType $type
 *   The foo type object.
 */
function foo_type_save(FooType $type) {
  $type->save();
}

/**
 * Deletes a foo type from the db.
 *
 * @param \FooType $type
 *   The foo type object.
 */
function foo_type_delete(FooType $type) {
  $type->delete();
}

/**
 * URI callback for foos.
 *
 * @param \Foo $foo
 *   The foo object.
 *
 * @return array
 *   URI callback.
 */
function foo_uri(Foo $foo) {
  return array(
    'path' => 'foo/' . $foo->foo_id,
  );
}

/**
 * Menu title callback for showing individual entities.
 *
 * @param \Foo $foo
 *   The foo object.
 *
 * @return string
 *   Menu title.
 */
function foo_page_title(Foo $foo) {
  return $foo->name;
}

/**
 * Sets up content to show an individual foo.
 *
 * @param \Foo $foo
 *   The foo object.
 * @param string   $view_mode
 *   View mode.
 *
 * @return mixed
 *   Content.
 */
function foo_page_view(Foo $foo, $view_mode = 'full') {
  $controller = entity_get_controller('foo');
  $content    = $controller->view(array($foo->foo_id => $foo));
  drupal_set_title($foo->name);

  return $content;
}