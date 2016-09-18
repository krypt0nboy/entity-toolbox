<?php

/**
 * @file
 */

/**
 * Number of seconds in a day.
 */
define('CACHE_DAILY', 86400);

/**
 * Number of seconds in a week.
 */
define('CACHE_WEEKLY', 604800);

/**
 * Cache cid for entity_toolbox cache info.
 * @see hook_entity_toolbox_cache_info().
 * @see entity_toolbox_cache_get_info().
 */
define('ENTITY_TOOLBOX__CACHE_INFO', 'entity_toolbox_cache_info');

/**
 * Cache cid for hook register info.
 * @see hook_hook_register_info().
 */
define('ENTITY_TOOLBOX__HOOK_REGISTER_INFO', 'entity_toolbox_hook_register_info');

/**
 * Cache cid for property type info.
 * @see hook_toolbox_property_type_info().
 * @see entity_toolbox_property_type_get_info().
 */
define('ENTITY_TOOLBOX__PROPERTY_TYPE_INFO', 'entity_toolbox_property_type_info');

/**
 * Cache cid for property widget info.
 * @see hook_toolbox_property_widget_info().
 * @see entity_toolbox_property_widget_get_info().
 */
define('ENTITY_TOOLBOX__PROPERTY_WIDGET_INFO', 'entity_toolbox_property_widget_info');

/**
 * Cache cid for schema type info.
 * @see hook_schema_type_info().
 * @see entity_toolbox_schema_type_get_info().
 */
define('ENTITY_TOOLBOX__SCHEMA_TYPE_INFO', 'schema_type_info');

/**
 * Cache cid for callback type info.
 * @see hook_toolbox_callback_type_info().
 * @see entity_toolbox_entity_callback_type_get_info().
 */
define('ENTITY_TOOLBOX__CALLBACK_TYPE_INFO', 'callback_type_info');

/**
 * Cache cid for action type info.
 * @see hook_toolbox_action_type_info().
 * @see entity_toolbox_entity_action_type_get_info().
 */
define('ENTITY_TOOLBOX__ACTION_TYPE_INFO', 'action_type_info');

/**
 * Cache cid for class type info.
 * @see hook_class_type_info().
 */
define('ENTITY_TOOLBOX__CLASS_TYPE_INFO', 'class_type_info');

/**
 * Cache cid for toolbox entity info.
 * @see hook_entity_toolbox_entity_info().
 * @see entity_toolbox_get_info().
 */
define('ENTITY_TOOLBOX__ENTITY_INFO', 'entity_info');

/**
 * Cache cid for toolbox entity info.
 * @see hook_entity_toolbox_entity_info().
 * @see entity_toolbox_get_info().
 */
define('ENTITY_TOOLBOX__TMP_ENTITY_INFO', 'tmp_entity_info');

/**
 * Cache cid to store generated entities schemas.
 */
define('ENTITY_TOOLBOX__ENTITY_SCHEMA', 'entity_schema');

/**
 * Cache cid for entity resources info.
 * @see hook_entity_resources_info().
 * @see entity_toolbox_entity_resources_get_info().
 */
define('ENTITY_TOOLBOX__ENTITY_RESOURCES_INFO', 'entity_resources_info');

/**
 * Cache cid for entity group info.
 */
define('ENTITY_TOOLBOX__ENTITY_GROUP_INFO', 'entity_group_info');

/**
 * Cache cid for entity group attach info.
 */
define('ENTITY_TOOLBOX__ENTITY_GROUP_ATTACH_INFO', 'entity_group_attach_info');

/**
 * Cache cid for field category group info.
 */
define('ENTITY_TOOLBOX__FIELD_CATEGORY_GROUP_INFO', 'field_category_group_info');

/**
 * Cache cid for field category info.
 */
define('ENTITY_TOOLBOX__FIELD_CATEGORY_INFO', 'field_category_info');

/**
 * Cache cid for parent property info.
 */
define('ENTITY_TOOLBOX__PARENT_PROPERTY_INFO', 'parent_property_info');

/**
 * Cache cid for inheritable info.
 */
define('ENTITY_TOOLBOX__INHERITABLE_PROPERTY_INFO', 'inheritable_property_info');

/**
 * Cache cid for inherited property info.
 */
define('ENTITY_TOOLBOX__INHERITED_PROPERTY_INFO', 'inherited_property_info');

/**
 * Cache cid for inheritable info.
 */
define('ENTITY_TOOLBOX__INHERITABLE_FIELD_INFO', 'inheritable_field_info');

/**
 * Cache cid for inherited field info.
 */
define('ENTITY_TOOLBOX__INHERITED_FIELD_INFO', 'inherited_field_info');

/**
 * Cache data fore entity toolbox in cache_entity_toolbox.
 * Sets the cache in entity_toolbox cache table.
 *
 * @param string $cid
 *   The cache ID.
 * @param mixed  $data
 *   The data to cache.
 * @param int    $expire
 *   The expiration in seconds.
 */
function entity_toolbox_cache_set($cid, $data, $expire = CACHE_PERMANENT) {
  $cache_enabled = variable_get('cache_enabled');
  list($expires, $cache) = array_values(entity_toolbox_cache_get_info($cid));
  if ($cache_enabled && $cache) {
    cache_set($cid, $data, ENTITY_TOOLBOX_DB__CACHE, isset($expires) ? $expires : $expire);
  }
}

/**
 * Returns cache from cache_entity_toolbox.
 * Gets the cache from entity_toolbox cache table.
 *
 * @param $cid
 *   The cache ID.
 *
 * @return null|object
 */
function entity_toolbox_cache_get($cid) {
  return cache_get($cid, ENTITY_TOOLBOX_DB__CACHE);
}

/**
 * Clear entity_toolbox cache.
 * Once cleared, related cache IDs are cleared as well.
 *
 * @param string $cid
 *   The entity toolbox cache ID.
 *
 * @see hook_entity_toolbox_cache_info().
 */
function entity_toolbox_cache_clear($cid) {
  cache_clear_all($cid, ENTITY_TOOLBOX_DB__CACHE);
  list(, $clears) = array_values(entity_toolbox_cache_get_info($cid));
  foreach ($clears as $clear) {
    cache_clear_all($clear, ENTITY_TOOLBOX_DB__CACHE);
  }
}

/**
 * Clear the cache for every entity_toolbox cache id.
 */
function entity_toolbox_cache_clear_all() {
  cache_clear_all('*', ENTITY_TOOLBOX_DB__CACHE, TRUE);
}

/**
 * Implements hook_entity_toolbox_cache_info().
 */
function entity_toolbox_entity_toolbox_cache_info() {
  $info                                            = array();
  $info[ENTITY_TOOLBOX__HOOK_REGISTER_INFO]        = array(
    'expires' => CACHE_PERMANENT
  );
  $info[ENTITY_TOOLBOX__CLASS_TYPE_INFO]           = array(
    'expires' => CACHE_PERMANENT
  );
  $info[ENTITY_TOOLBOX__PROPERTY_TYPE_INFO]        = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX__PROPERTY_WIDGET_INFO]      = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX__SCHEMA_TYPE_INFO]          = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX__CALLBACK_TYPE_INFO]        = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX__ENTITY_INFO]               = array(
    'expires' => CACHE_PERMANENT,
    'cache'   => TRUE,
    'clear'   => array(
      ENTITY_TOOLBOX__ENTITY_GROUP_INFO,
      ENTITY_TOOLBOX__ENTITY_GROUP_ATTACH_INFO,
      ENTITY_TOOLBOX__INHERITABLE_PROPERTY_INFO,
      ENTITY_TOOLBOX__INHERITED_PROPERTY_INFO,
      ENTITY_TOOLBOX__INHERITABLE_FIELD_INFO,
      ENTITY_TOOLBOX__FIELD_CATEGORY_GROUP_INFO,
      ENTITY_TOOLBOX__FIELD_CATEGORY_INFO,
    ),
    'hooks'   => array(
      //@todo add hook_module_pre_install
      'module_pre_install',
    )
  );
  $info[ENTITY_TOOLBOX__TMP_ENTITY_INFO]           = array(
    'expires' => CACHE_PERMANENT,
    'cache'   => TRUE,
  );
  $info[ENTITY_TOOLBOX__PARENT_PROPERTY_INFO]           = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX__ENTITY_SCHEMA]             = array(
    'expires' => CACHE_PERMANENT,
    'clear'   => array(),
    'hooks'   => array(
      'module_install',
    )
  );
  $info[ENTITY_TOOLBOX__ENTITY_GROUP_INFO]         = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX__FIELD_CATEGORY_GROUP_INFO] = array(
    'expires' => CACHE_PERMANENT
  );
  $info[ENTITY_TOOLBOX__FIELD_CATEGORY_INFO]       = array(
    'expires' => CACHE_PERMANENT
  );
  $info[ENTITY_TOOLBOX__ENTITY_GROUP_ATTACH_INFO]  = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX__INHERITABLE_PROPERTY_INFO] = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX__INHERITED_PROPERTY_INFO]   = array(
    'expires' => CACHE_PERMANENT,
    'cache' => FALSE,
  );
  $info[ENTITY_TOOLBOX__INHERITABLE_FIELD_INFO]    = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX__FIELD_CATEGORY_GROUP_INFO] = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX__FIELD_CATEGORY_INFO]       = array(
    'expires' => CACHE_PERMANENT,
  );

  return $info;
}