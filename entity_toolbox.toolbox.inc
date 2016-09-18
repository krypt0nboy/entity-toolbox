<?php

/**
 * @file
 *
 * This file contains the functions required to extract, process and store information provided by entity_toolbox hooks.
 */

/**
 * Returns info on an entity toolbox cache cid,
 * such as "expires".
 * Unlike any other entity toolbox cache element, this one is stored in "cache"
 * to avoid errors when retrieving and processing the cache info.
 *
 * @param null $cid
 *   The cid, or NULL to return info on all cid's.
 *
 * @return array
 *
 * @see hook_entity_toolbox_cache_info().
 */
function entity_toolbox_cache_get_info($cid = NULL) {

  /**
   * We cache it since its used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast[ENTITY_TOOLBOX__CACHE_INFO] = &drupal_static(__FUNCTION__);
  }

  $entity_toolbox_cache_info = &$drupal_static_fast[ENTITY_TOOLBOX__CACHE_INFO];
  if (empty($entity_toolbox_cache_info)) {
    if ($cache = cache_get(ENTITY_TOOLBOX__CACHE_INFO)) {
      $entity_toolbox_cache_info = $cache->data;
    }
    else {
      $data = module_invoke_all('entity_toolbox_cache_info');
      drupal_alter('entity_toolbox_cache_info', $data);
      $info = array();
      foreach ($data as $key => $value) {
        $value += array(
          'cache' => TRUE
        );
        $info[$key] = $value;
      }

      $entity_toolbox_cache_info = $info;
      cache_set(ENTITY_TOOLBOX__CACHE_INFO, $entity_toolbox_cache_info);
    }
  }

  return isset($cid) ? $entity_toolbox_cache_info[$cid] : $entity_toolbox_cache_info;
}

/**
 * Returns the hooks on which entity toolbox cache IDs should be cleared.
 *
 * @param string $hook
 *   The hook name.
 *
 * @return string[]
 */
function entity_toolbox_cache_hook_get_info($hook) {
  $hooks = &drupal_static(__FUNCTION__, array());
  if (!isset($hooks[$hook])) {
    $cache_info = entity_toolbox_cache_get_info();
    foreach ($cache_info as $cid => $info) {
      if (!empty($info['hooks'][$hook])) {
        $hooks[$hook][] = $cid;
      }
    }
  }

  return $hooks[$hook];
}

/**
 * Returns a list of hooks set to clear some cache cid when invoked.
 *
 * @return string[]
 */
function entity_toolbox_cache_hooks_get_info() {
  $hooks = &drupal_static(__FUNCTION__, array());
  if (!isset($hooks)) {
    $cache_info = entity_toolbox_cache_get_info();
    $buffer     = array();
    foreach ($cache_info as $cid => $info) {
      foreach ($info['hooks'] as $hook) {
        $buffer[] = $hook;
      }
    }
    $hooks = array_unique($buffer);
  }

  return $hooks;
}

/**
 * Returns the available hooks builders info.
 *
 * @param null $hook
 *   The hook name, or NULL to return all hooks.
 *
 * @return array
 *
 * @see hook_hook_register_info().
 */
function entity_toolbox_hook_get_info($hook = NULL) {
  $HOOK     = 'hook_register_info';
  $CACHEKEY = ENTITY_TOOLBOX__HOOK_REGISTER_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['hook_register_info'] = &drupal_static(__FUNCTION__);
  }

  $hook_register_info = &$drupal_static_fast['hook_register_info'];
  if (empty($hook_register_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $hook_register_info = $cache->data;
    }
    else {
      $data = module_invoke_all($HOOK);
      drupal_alter($HOOK, $data);
      $hook_register_info = $data;
      entity_toolbox_cache_set($CACHEKEY, $hook_register_info);
    }
  }

  return isset($hook) ? $hook_register_info[$hook] : $hook_register_info;
}

/**
 * Returns the classes types declared in entity_toolbox.
 *
 * @param string $class
 *   The class type, or NULL to return info on evert class type.
 *
 * @return array|null
 */
function entity_toolbox_class_type_get_info($class = NULL) {
  $HOOK     = 'class_type_info';
  $CACHEKEY = ENTITY_TOOLBOX__CLASS_TYPE_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['class_type_info'] = &drupal_static(__FUNCTION__);
  }

  $class_type_info = &$drupal_static_fast['class_type_info'];
  if (empty($class_type_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $class_type_info = $cache->data;
    }
    else {
      $data = module_invoke_all($HOOK);
      drupal_alter($HOOK, $data);
      $class_type_info = $data;
      entity_toolbox_cache_set($CACHEKEY, $class_type_info);
    }
  }

  return isset($class) ? $class_type_info[$class] : $class_type_info;
}

/**
 * Returns info on an entity_toolbox property type.
 *
 * @param null $property_type
 *   The property type, or NULL to return all property types.
 *
 * @return array
 *
 * @see hook_toolbox_property_type_info().
 */
function entity_toolbox_property_type_get_info($property_type = NULL) {
  $HOOK     = 'toolbox_property_type_info';
  $CACHEKEY = ENTITY_TOOLBOX__PROPERTY_TYPE_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['property_type_info'] = &drupal_static(__FUNCTION__);
  }

  $property_type_info = &$drupal_static_fast['property_type_info'];
  if (empty($property_type_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $property_type_info = $cache->data;
    }
    else {
      $data = module_invoke_all($HOOK);
      drupal_alter($HOOK, $data);

      $types = array();
      foreach ($data as $type => $info) {
        $types[$type] = $info;
      }

      $property_type_info = $types;
      entity_toolbox_cache_set($CACHEKEY, $property_type_info);
    }
  }

  return isset($property_type) ? $property_type_info[$property_type] : $property_type_info;
}

/**
 * Returns info on a widget type.
 *
 * @param null $widget
 *   The widget name, or NULL to return info on all widgets.
 *
 * @return array
 *
 * @see hook_toolbox_property_widget_info().
 */
function entity_toolbox_property_widget_get_info($widget = NULL) {
  $HOOK     = 'toolbox_property_widget_info';
  $CACHEKEY = ENTITY_TOOLBOX__PROPERTY_WIDGET_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['property_type_info'] = &drupal_static(__FUNCTION__);
  }

  $property_widget_info = &$drupal_static_fast['property_widget_info'];
  if (empty($property_widget_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $property_widget_info = $cache->data;
    }
    else {
      $data = module_invoke_all($HOOK);
      drupal_alter($HOOK, $data);

      $types = array();
      foreach ($data as $type => $info) {
        $types[$type] = $info;
      }

      $property_widget_info = $types;
      entity_toolbox_cache_set($CACHEKEY, $property_widget_info);
    }
  }

  return isset($widget) ? $property_widget_info[$widget] : $property_widget_info;
}

/**
 * Returns info on schema types (or table types), such as base table, revision table, etc...
 *
 * @param null|string $schema_type
 *   The schema type, or NULL to return info on all schema types.
 *
 * @return array
 *
 * @see hook_schema_type_info().
 */
function entity_toolbox_schema_type_get_info($schema_type = NULL) {
  $HOOK     = 'schema_type_info';
  $CACHEKEY = ENTITY_TOOLBOX__SCHEMA_TYPE_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['schema_type_info'] = &drupal_static(__FUNCTION__);
  }

  $schema_type_info = &$drupal_static_fast['schema_type_info'];
  if (empty($schema_type_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $schema_type_info = $cache->data;
    }
    else {
      $data = module_invoke_all($HOOK);
      drupal_alter($HOOK, $data);

      $types = array();
      foreach ($data as $type => $info) {
        $types[$type] = $info;
      }

      $schema_type_info = $types;
      entity_toolbox_cache_set($CACHEKEY, $schema_type_info);
    }
  }

  return isset($schema_type) ? $schema_type_info[$schema_type] : $schema_type_info;
}

/**
 * Returns an entity callback type info.
 * Callbacks declared in the hook_toolbox_callback_type_info() are default and often required callbacks for an entity.
 *
 * @param null $type
 *   The callback type.
 *
 * @return array
 *
 * @see hook_toolbox_callback_type_info()
 */
function entity_toolbox_entity_callback_type_get_info($type = NULL) {
  $HOOK     = 'toolbox_callback_type_info';
  $CACHEKEY = ENTITY_TOOLBOX__CALLBACK_TYPE_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['callback_type_info'] = &drupal_static(__FUNCTION__);
  }

  $callback_type_info = &$drupal_static_fast['callback_type_info'];
  if (empty($callback_type_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $callback_type_info = $cache->data;
    }
    else {
      $types = array();
      $data  = module_invoke_all($HOOK);
      drupal_alter($HOOK, $data);
      foreach ($data as $callback => $info) {
        $types[$callback] = $info;
      }
      $callback_type_info = $types;
      entity_toolbox_cache_set($CACHEKEY, $callback_type_info);
    }
  }

  return isset($type) ? $callback_type_info[$type] : $callback_type_info;
}

/**
 * Returns a module entity_toolbox settings, declared in the module's info file.
 *
 * @param string $module
 *   The module's name.
 *
 * @return mixed
 */
function entity_toolbox_module_info_get_info($module) {
  $modules = &drupal_static(__FUNCTION__, array());
  if (!in_array($module, $modules)) {
    $info_file = drupal_parse_info_file(drupal_get_path('module', $module) . '/' . $module . '.info');
    if (!empty($info_file['entity_toolbox'])) {
      $info          = $info_file['entity_toolbox'];
      $function      = $module . '_entity_toolbox_info';
      $info2obj      = new stdClass();
      $info2obj->api = $info['toolbox_api'][0];
      if (function_exists($function)) {
        $module_invoke      = $function();
        $module_entities    = array_keys($module_invoke);
        $info2obj->entities = $module_entities;
      }
      $function = $module . '_entity_group_info';
      if (function_exists($function)) {
        $module_invoke           = $function();
        $entity_groups           = array_keys($module_invoke);
        $info2obj->entity_groups = $entity_groups;
      }
      $modules[$module] = $info2obj;
    }
  }

  return $modules[$module];
}

/**
 * Returns a module entity_toolbox api, declared in the module's info file.
 *
 * @param string $module
 *   The module's name.
 *
 * @return mixed
 */
function entity_toolbox_module_api_get_info($module) {
  $modules = &drupal_static(__FUNCTION__, array());
  if (!in_array($module, $modules)) {
    $info             = entity_toolbox_module_info_get_info($module);
    $modules[$module] = $info->api;
  }

  return $modules[$module];
}

/**
 * Returns entities info declared through entity_toolbox.
 *
 * @param null|string $entity_type
 *   The machine_name of the entity for which to get the info or NULL to return an array for all the entities.
 *
 * @param null|int    $update_N
 *   The update number for an entity type, or NULL to returns info with no updates.
 *
 * @see hook_entity_toolbox_entity_info().
 * @see hook_entity_toolbox_entity_info_alter().
 * @see hook_entity_toolbox_ENTITY_TYPE_properties_update_N().
 *
 * @return array
 */
function entity_toolbox_get_info($entity_type = NULL, $update_N = NULL, $reset = FALSE) {
  /** @var string $HOOK */
  $HOOK = 'entity_toolbox_info';
  /** @var string $CACHEKEY */
  $CACHEKEY = ENTITY_TOOLBOX__ENTITY_INFO;
  /** @var string $TMP_CACHEKEY */
  $TMP_CACHEKEY = ENTITY_TOOLBOX__TMP_ENTITY_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['entity_toolbox_info'] = &drupal_static(__FUNCTION__);
  }

  if ($reset) {
    entity_toolbox_cache_clear_all();
    $entity_toolbox_info = NULL;
  }
  else {
    $entity_toolbox_info = &$drupal_static_fast['entity_toolbox_info'];
  }

  if (empty($entity_toolbox_info)) {
    if (($cache = entity_toolbox_cache_get($CACHEKEY)) && (!$reset)) {
      $entity_toolbox_info = $cache->data;
    }
    else {
      $data    = array();
      $modules = module_implements($HOOK);
      foreach ($modules as $module) {
        $function = $module . '_' . $HOOK;
        $call     = $function();
        /**
         * @var string $t
         * @var array  $v
         */
        foreach ($call as $t => $v) {
          $v['module'] = !empty($v['module']) ? $v['module'] : $module;
          $data[$t]    = $v;
        }
      }
      $processed = array();
      /**
       * @var string $type
       *   Matches an entity type.
       * @var array  $info
       *   The matching entity type raw info, as retrieved in module_invoke().
       */
      foreach ($data as $type => $info) {
        $args             = array(
          'entity_type' => $type,
          'raw_data'    => $info
        );
        $processed[$type] = entity_toolbox_info_build($type, $args);
        $tmp_cached       = entity_toolbox_cache_get($TMP_CACHEKEY);
        $tmp_cached       = !empty($tmp_cached) ? $tmp_cached->data : array();
        $tmp_cache        = is_empty($tmp_cached) ? array($type => $processed[$type]) : $tmp_cached + array($type => $processed[$type]);
        entity_toolbox_cache_set($TMP_CACHEKEY, $tmp_cache);
      }
      $entity_toolbox_info = $processed;
      entity_toolbox_cache_set($CACHEKEY, $entity_toolbox_info);
    }
  }

  if (isset($entity_type)) {
    if ($reset) {
      return !empty($entity_toolbox_info[$entity_type]) ? $entity_toolbox_info[$entity_type] : NULL;
    }
    else {
      return !empty($entity_toolbox_info[$entity_type]) ? $entity_toolbox_info[$entity_type] : entity_toolbox_get_info($entity_type, $update_N, TRUE);
    }
  }
  else {
    return $entity_toolbox_info;
  }
}

/**
 * Returns the equivalent of entity_get_info(),except that it does not take
 * into account entities declared through hook_entity_toolbox_info().
 * This function avoids infinite loops when reference properties are built.
 *
 * @param null|string $entity_type
 *   The entity type.
 *
 * @return array
 */
function pre_build_entity_get_info($entity_type = NULL) {
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['entity_info'] = &drupal_static(__FUNCTION__);
  }
  $entity_info = &$drupal_static_fast['entity_info'];
  if (empty($entity_info)) {
    // Modules implementing hook_entity_info.
    $entity_info_implement = module_implements('entity_info');
    // Modules implementing hook_entity_toolbox_info.
    $toolbox_info_implement = module_implements('entity_toolbox_info');
    // Excludes the toolbox modules from being invoked below.
    $excludes    = array_intersect($entity_info_implement, $toolbox_info_implement);
    $includes    = array_diff($entity_info_implement, $excludes);
    $entity_info = array();
    foreach ($includes as $include) {
      $function = $include . '_entity_info';
      $entity_info += $function();
    }
    // Taken from entity_get_info().
    foreach ($entity_info as $name => $data) {
      $entity_info[$name] += array(
        'fieldable'        => FALSE,
        'controller class' => 'DrupalDefaultEntityController',
        'static cache'     => TRUE,
        'field cache'      => TRUE,
        'load hook'        => $name . '_load',
        'bundles'          => array(),
        'view modes'       => array(),
        'entity keys'      => array(),
        'translation'      => array(),
      );
      $entity_info[$name]['entity keys'] += array(
        'revision' => '',
        'bundle'   => '',
      );
      foreach ($entity_info[$name]['view modes'] as $view_mode => $view_mode_info) {
        $entity_info[$name]['view modes'][$view_mode] += array(
          'custom settings' => FALSE,
        );
      }
      // If no bundle key is provided, assume a single bundle, named after
      // the entity type.
      if (empty($entity_info[$name]['entity keys']['bundle']) && empty($entity_info[$name]['bundles'])) {
        $entity_info[$name]['bundles'] = array($name => array('label' => $entity_info[$name]['label']));
      }
      // Prepare entity schema fields SQL info for
      // DrupalEntityControllerInterface::buildQuery().
      if (isset($entity_info[$name]['base table'])) {
        $entity_info[$name]['base table field types']          = drupal_schema_field_types($entity_info[$name]['base table']);
        $entity_info[$name]['schema_fields_sql']['base table'] = drupal_schema_fields_sql($entity_info[$name]['base table']);
        if (isset($entity_info[$name]['revision table'])) {
          $entity_info[$name]['schema_fields_sql']['revision table'] = drupal_schema_fields_sql($entity_info[$name]['revision table']);
        }
      }
    }
  }
  if (empty($entity_type)) {
    return $entity_info;
  }
  elseif (isset($entity_info[$entity_type])) {
    return $entity_info[$entity_type];
  }
}

/**
 * @return array
 */
function entity_toolbox_get_entities() {
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['entity_toolbox_entities'] = &drupal_static(__FUNCTION__);
  }
  $entity_toolbox_entities = &$drupal_static_fast['entity_toolbox_entities'];
  if (empty($entity_toolbox_entities)) {
    $entity_toolbox_entities = array_keys(module_invoke_all('entity_toolbox_info'));
  }

  return $entity_toolbox_entities;
}

/**
 * Returns the module managing an entity type.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string
 */
function entity_get_module_info($entity_type) {
  $entities = &drupal_static(__FUNCTION__, array());
  if (empty($entities)) {
    $modules      = module_implements('entity_toolbox_info');
    $entity_types = array();
    foreach ($modules as $module) {
      $invoke = $module . '_entity_toolbox_info';
      $types  = array_keys($invoke());
      $types  = array_fill_keys($types, $module);
      $entity_types += $types;
    }
    $entities = $entity_types;
  }

  return $entities[$entity_type];
}

/**
 * Indicates if an entity type is managed by entity toolbox.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return bool
 */
function is_entity_toolbox_entity($entity_type) {
  return in_array($entity_type, entity_toolbox_get_entities());
}

/**
 * Returns entities classes declared through entity_toolbox.
 *
 * @param null|string $entity_type
 *   The entity type, or NULL to return info on every entity type.
 * @param null|string $class
 *   The class type, or NULL to return info on every class type.
 *
 * @return array
 *
 * @see hook_entity_class_info().
 * @deprecated
 */
function entity_toolbox_get_entity_class_info($entity_type = NULL, $class = NULL) {

}

/**
 * Returns a cached built schema.
 * Caching generated schemas is more reliable and avoids performance losses.
 *
 * @param null|string $entity_type
 *   The entity type, or NULL to return every entity type schemas.
 * @param bool        $reset
 *   A boolean to clear the cached generated schemas, defaults to FALSE.
 *
 * @return array
 */
function entity_toolbox_get_schema($entity_type = NULL, $reset = FALSE) {
  $CACHEKEY = ENTITY_TOOLBOX__ENTITY_SCHEMA;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['entity_schema'] = &drupal_static(__FUNCTION__);
  }
  $entity_schema = &$drupal_static_fast['entity_schema'];

  //If entity type is specified and that the system does not detect it, then reset the cache and generate the schema.
  $reset = (isset($entity_type) && !entity_install_get_info($entity_type)) && !$reset;

  if (empty($entity_schema) && !$reset) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $entity_schema = $cache->data;
    }
    else {
      $buffer = array();
      foreach (entity_toolbox_get_info() as $type => $info) {
        foreach (entity_schemas_build($type) as $schemas) {
          foreach ($schemas as $schema_name => $schema) {
            $buffer[$type][$schema_name] = $schema;
          }
        }
      }
      $entity_schema = $buffer;
      entity_toolbox_cache_set($CACHEKEY, $entity_schema);
    }
  }

  return isset($entity_type) ? $entity_schema[$entity_type] : $entity_schema;
}

/**
 * Returns the entity groups declared.
 *
 * @param null|string $group
 *   The entity group name or NULL to return all groups.
 *
 * @return array
 *
 * @see hook_entity_toolbox_entity_group_info().
 */
function entity_toolbox_entity_group_get_info($group = NULL) {
  $HOOK     = 'entity_group_info';
  $CACHEKEY = ENTITY_TOOLBOX__ENTITY_GROUP_INFO;

  /**
   * Cached since its used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['entity_groups'] = &drupal_static(__FUNCTION__);
  }

  $entity_groups = &$drupal_static_fast['entity_groups'];
  if (empty($entity_groups)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $entity_groups = $cache->data;
    }
    else {
      $groups = array();
      $data   = module_invoke_all($HOOK);
      drupal_alter($HOOK, $data);
      $groups_entities = array();
      $toolbox_invoke  = module_invoke_all('entity_toolbox_info');
      drupal_alter('entity_toolbox_info', $toolbox_invoke);
      foreach ($toolbox_invoke as $entity_type => $info) {
        if (!empty($info['group'])) {
          $groups_entities[$info['group']][] = $entity_type;
        }
      }
      foreach ($data as $name => $group_info) {
        $group_info['entity_types'] = !empty($groups_entities[$name]) ? $groups_entities[$name] : array();
        foreach (entity_toolbox_field_category_group_get_info() as $field_category_group => $field_category_group_info) {
          if ($field_category_group_info['group'] == $name) {
            $group_info['field_category_groups'][$field_category_group] = $field_category_group_info;
          }
        }
        $groups[$name] = $group_info;
      }
      $entity_groups = $groups;
      entity_toolbox_cache_set($CACHEKEY, $entity_groups);
    }
  }

  return isset($group) ? $entity_groups[$group] : $entity_groups;

}

/**
 * Returns a group attached entity types.
 *
 * @param null|string $group
 *   The group name.
 *
 * @return array
 *
 * @see hook_group_attach_info().
 * @deprecated
 */
function entity_toolbox_entity_group_attach_get_info($group = NULL) {
  $CACHEKEY = ENTITY_TOOLBOX__ENTITY_GROUP_ATTACH_INFO;

  /**
   * Cached since its used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['group_attach_info'] = &drupal_static(__FUNCTION__);
  }

  $group_attach_info = &$drupal_static_fast['group_attach_info'];
  if (empty($group_attach_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $group_attach_info = $cache->data;
    }
    else {
      $groups = array();
      $data   = module_invoke_all('entity_group_attach_info');
      drupal_alter('entity_group_attach_info', $data);
      foreach ($data as $entity_type => $group_name) {
        $groups[$group_name] = $entity_type;
      }
      $group_attach_info = $groups;
      entity_toolbox_cache_set($CACHEKEY, $group_attach_info);
    }
  }

  return isset($group) ? $group_attach_info[$group] : $group_attach_info;
}

/**
 * Returns info on a field category group.
 *
 * @param null|string $group
 *   The field category group name.
 *
 * @return array
 *
 * @see hook_entity_toolbox_field_category_group_info().
 */
function entity_toolbox_field_category_group_get_info($group = NULL) {
  $HOOK     = 'field_category_group_info';
  $CACHEKEY = ENTITY_TOOLBOX__FIELD_CATEGORY_GROUP_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['field_category_group_info'] = &drupal_static(__FUNCTION__);
  }

  $field_category_group_info = &$drupal_static_fast['field_category_group_info'];
  if (empty($field_category_group_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $field_category_group_info = $cache->data;
    }
    else {
      $groups = array();
      $data   = module_invoke_all($HOOK);
      drupal_alter($HOOK, $data);
      foreach ($data as $name => $info) {
        $groups[$name] = $info;
        foreach (entity_toolbox_field_category_get_info() as $field_category => $field_category_info) {
          if ($field_category_info['group'] == $name) {
            $groups[$name]['field_categories'][] = $field_category;
          }
        }
      }
      $field_category_group_info = $groups;
      entity_toolbox_cache_set($CACHEKEY, $field_category_group_info);
    }
  }

  return isset($group) ? $field_category_group_info[$group] : $field_category_group_info;
}

/**
 * Returns info on a field category.
 *
 * @param null|string $category
 *   The field category name.
 *
 * @return array
 *
 * @see hook_entity_toolbox_field_category_info().
 */
function entity_toolbox_field_category_get_info($category = NULL) {
  $HOOK     = 'field_category_info';
  $CACHEKEY = ENTITY_TOOLBOX__FIELD_CATEGORY_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['field_category_info'] = &drupal_static(__FUNCTION__);
  }

  $field_category_info = &$drupal_static_fast['field_category_info'];
  if (empty($field_category_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $field_category_info = $cache->data;
    }
    else {
      $groups = array();
      $data   = module_invoke_all($HOOK);
      drupal_alter($HOOK, $data);
      foreach ($data as $name => $info) {
        $groups[$name] = $info;
      }
      $field_category_info = $groups;
      entity_toolbox_cache_set($CACHEKEY, $field_category_info);
    }
  }

  return isset($category) ? $field_category_info[$category] : $field_category_info;
}

/**
 * Returns an entity type parent properties.
 *
 * @param null $entity_type
 *   The entity type, or NULL to return parent properties for all entity types.
 *
 * @return array
 */
function entity_toolbox_entity_parent_properties_get_info($entity_type = NULL) {

  $CACHEKEY = ENTITY_TOOLBOX__PARENT_PROPERTY_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['parent_property_info'] = &drupal_static(__FUNCTION__);
  }

  $parent_property_info = &$drupal_static_fast['parent_property_info'];
  if (empty($parent_property_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $parent_property_info = $cache->data;
    }
    else {
      $parents = array();
      foreach (entity_toolbox_get_info() as $type => $info) {
        foreach ($info['properties'] as $prop_name => $property) {
          if (($property['type'] == 'parent') || ($property['type'] == 'self_parent')) {
            //The key is the property name and the value is the parent entity_type.
            $parents[$type][$prop_name] = $property['reference'];
          }
        }
      }
      $parent_property_info = $parents;
      entity_toolbox_cache_set($CACHEKEY, $parent_property_info);
    }
  }

  return isset($entity_type) ? $parent_property_info[$entity_type] : $parent_property_info;
}

/**
 * Returns the inheritable property of an entity type.
 *
 * @param null|string $entity_type
 *   The entity type, or NULL to return info on all entity types.
 *
 * @return array
 */
function entity_toolbox_inheritable_property_get_info($entity_type = NULL) {
  $CACHEKEY = ENTITY_TOOLBOX__INHERITABLE_PROPERTY_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['inheritable_property_info'] = &drupal_static(__FUNCTION__);
  }

  $inheritable_property_info = &$drupal_static_fast['inheritable_property_info'];
  if (empty($inheritable_property_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $inheritable_property_info = $cache->data;
    }
    else {
      $inheritable = array();
      foreach (entity_toolbox_get_info() as $type => $info) {
        foreach ($info['children_inherit'] as $inherit) {
          $inheritable[$type][] = $inherit;
        }
      }
      $inheritable_property_info = $inheritable;
      entity_toolbox_cache_set($CACHEKEY, $inheritable_property_info);
    }
  }

  return isset($entity_type) ? $inheritable_property_info[$entity_type] : $inheritable_property_info;
}

/**
 * Returns the inherited properties of an entity type.
 *
 * @param null $entity_type
 *   The entity type, or NULL to return properties for every entity type.
 *
 * @return array
 */
function entity_toolbox_inherited_property_get_info($entity_type = NULL) {
  $CACHEKEY = ENTITY_TOOLBOX__INHERITED_PROPERTY_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['inherited_property_info'] = &drupal_static(__FUNCTION__);
  }

  $inherited_property_info = &$drupal_static_fast['inherited_property_info'];
  if (empty($inherited_property_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $inherited_property_info = $cache->data;
    }
    else {
      $inherited = array();
      foreach (entity_toolbox_get_info() as $type => $info) {
        $buffer = array();
        /**
         * @var string $prop_name
         *   The property name.
         * @var string $parent_type
         *   The parent entity type.
         */
        foreach (entity_toolbox_entity_parent_properties_get_info($type) as $prop_name => $parent_type) {
          //@todo mind parent type hierarchy position in the entity group.
          //The inheritable properties for the current parent type.
          foreach (entity_toolbox_inheritable_property_get_info($parent_type) as $inheritable) {
            $buffer[$parent_type][] = $inheritable;
          }
        }
        $inherited[$type] = $buffer;
      }
      $inherited_property_info = $inherited;
      entity_toolbox_cache_set($CACHEKEY, $inherited_property_info);
    }
  }

  return isset($entity_type) ? $inherited_property_info[$entity_type] : $inherited_property_info;
}

/**
 * Returns fields to be inherited by children entities.
 *
 * @param null|string $entity_type
 *   The entity type.
 * @param null|string $bundle
 *   The bundle name.
 * @param null|string $field
 *   The field name.
 *
 * @return array
 *   An associative array where the keys are the entity types and the values are :
 *     - The entity type bundles : An array containing the name of inheritable fields.
 */
function entity_toolbox_inheritable_field_get_info($entity_type = NULL, $bundle = NULL, $field = NULL) {
  $CACHEKEY = ENTITY_TOOLBOX__INHERITABLE_FIELD_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['inheritable_field_info'] = &drupal_static(__FUNCTION__);
  }

  $inheritable_field_info = &$drupal_static_fast['inheritable_field_info'];
  if (empty($inheritable_field_info)) {
    if ($cache = entity_toolbox_cache_get(ENTITY_TOOLBOX__INHERITABLE_FIELD_INFO)) {
      $inheritable_field_info = $cache->data;
    }
    else {
      $inheritable = array();
      foreach (entity_toolbox_get_info() as $type => $info) {
        foreach (entity_get_types($type) as $bnd) {
          foreach (field_info_instances($type, $bnd) as $field_info_instance) {
            if (isset($field_info_instance['settings']['toolbox']['inherit'])) {
              $inheritable[$type][$bnd][] = $field_info_instance['name'];
            }
          }
        }
      }
      $inheritable_field_info = $inheritable;
      entity_toolbox_cache_set($CACHEKEY, $inheritable_field_info);
    }
  }

  if (isset($entity_type)) {
    if (isset($bundle)) {
      return isset($field) ? $inheritable_field_info[$entity_type][$bundle][$field] : $inheritable_field_info[$entity_type][$bundle];
    }
    else {
      return $inheritable_field_info[$entity_type];
    }
  }
  else {
    return $inheritable_field_info;
  }
}

/**
 * Returns fields that should inherit parent values.
 *
 * @param null|string $entity_type
 *   The entity type.
 * @param null|string $bundle
 *   The entity bundle.
 * @param null|string $field
 *   The field name.
 *
 * @return array
 */
function entity_toolbox_inherited_field_get_info($entity_type = NULL, $bundle = NULL, $field = NULL) {
  $CACHEKEY = ENTITY_TOOLBOX__INHERITED_FIELD_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['inherited_field_info'] = &drupal_static(__FUNCTION__);
  }

  $inherited_field_info = &$drupal_static_fast['inherited_field_info'];
  if (empty($inherited_field_info)) {
    if ($cache = entity_toolbox_cache_get(ENTITY_TOOLBOX__INHERITABLE_FIELD_INFO)) {
      $inherited_field_info = $cache->data;
    }
    else {
      $inherited   = array();
      $inheritable = entity_toolbox_inheritable_field_get_info();
      foreach (entity_toolbox_get_info() as $type => $info) {
        /**
         * @var string $b
         *   A bundle of $type.
         */
        foreach (entity_get_bundles($type) as $b) {
          $fields = field_info_instances($entity_type, $b);
          /**
           * @var string $f
           * @var array  $i
           */
          foreach ($fields as $f => $i) {

          }
        }
      }
      $inherited_field_info = $inherited;
      entity_toolbox_cache_set($CACHEKEY, $inherited_field_info);
    }
  }

  if (isset($entity_type)) {
    if (isset($bundle)) {
      return isset($field) ? $inherited_field_info[$entity_type][$bundle][$field] : $inherited_field_info[$entity_type][$bundle];
    }
    else {
      return $inherited_field_info[$entity_type];
    }
  }
  else {
    return $inherited_field_info;
  }

}

/**
 * Returns the entities edit form alters.
 *
 * @return array
 */
function entity_toolbox_edit_form_alter_get_info() {
  $calls = &drupal_static(__FUNCTION__, NULL);
  if (empty($calls)) {
    $regexp    = '/^(?P<module>.+)_type_(?P<entity_type>.+)_edit_form__alter$/';
    $functions = get_defined_functions();
    $calls     = array();
    foreach (preg_grep('/__alter$/', $functions['user']) as $function) {
      if (preg_match($regexp, $function, $matches)) {
        $calls[$matches['module']][] = $matches['entity_type'];
      }
    }
  }

  return $calls;
}

/**
 * Returns the entities delete form alters.
 *
 * @return array
 */
function entity_toolbox_delete_form_alter_get_info() {
  $calls = &drupal_static(__FUNCTION__, NULL);
  if (empty($calls)) {
    $regexp    = '/^(?P<module>.+)_type_(?P<entity_type>.+)_delete_form__alter$/';
    $functions = get_defined_functions();
    $calls     = array();
    foreach (preg_grep('/__alter$/', $functions['user']) as $function) {
      if (preg_match($regexp, $function, $matches)) {
        $calls[$matches['module']][] = $matches['entity_type'];
      }
    }
  }

  return $calls;
}

/**
 * Returns the entities inline entity form alters.
 *
 * @return array
 */
function entity_toolbox_inline_form_alter_get_info() {
  $calls = &drupal_static(__FUNCTION__, NULL);
  if (empty($calls)) {
    $regexp    = '/^(?P<module>.+)_type_(?P<entity_type>.+)_inline_entity_form__alter/';
    $functions = get_defined_functions();
    $calls     = array();
    foreach (preg_grep('/__alter$/', $functions['user']) as $function) {
      if (preg_match($regexp, $function, $matches)) {
        $calls[$matches['module']][] = $matches['entity_type'];
      }
    }
  }

  return $calls;
}

/**
 * Returns the module implementing hook_entity_skip_load().
 * Used in entity_skip_load().
 *
 * @return array
 *
 * @see hook_entity_skip_load().
 * @see _entity_skip_load().
 */
function entity_toolbox_entity_skip_load_get_info() {
  $calls = &drupal_static(__FUNCTION__, NULL);
  if (empty($calls)) {
    $regexp    = '/^(?P<module>.+)_entity_skip_load$/';
    $functions = get_defined_functions();
    $calls     = array();
    foreach ($functions['user'] as $function) {
      if (preg_match($regexp, $function, $matches)) {
        $calls[] = $matches['module'];
      }
    }
  }

  return $calls;
}

/**
 * Indicates if an entity is installed.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return bool
 */
function entity_install_get_info($entity_type) {
  $installed = &drupal_static(__FUNCTION__, array());
  if (!in_array($entity_type, $installed)) {
    $info = entity_get_info();
    if (in_array($entity_type, array_keys($info))) {
      if (db_table_exists($info[$entity_type]['base table'])) {
        $installed[] = $entity_type;
      }
    }
  }

  return in_array($entity_type, $installed);
}