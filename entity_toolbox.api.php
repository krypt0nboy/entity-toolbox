<?php

/**
 * @file
 *
 * @author Harold Cohen AKA kryptonboy <me@harold-cohen.com>
 * @license MIT
 * @version 0.9.2
 *
 * This file contains the api documentation for entity_toolbox.
 *
 * Entity toolbox allows to easily create and manage entities.
 *
 * The module offers the following features :
 *  - Auto hook data building
 *  - Entity groups
 *  - Behavior and properties heritage
 */

/**
 * Declares cache cid for cache_entity_toolbox.
 *
 * @return array
 *   An associative array where the keys are the cache name and whose values are :
 *   - expires : The duration of the cache in seconds.
 *   - clear : An array of cache cids to clear when clearing this one.
 *   - hooks : An array where the values hook names, which when invoked will clear the cid cache.
 */
function hook_entity_toolbox_cache_info() {
  $info               = array();
  $info['cache_name'] = array(
    'expires' => CACHE_PERMANENT,
    'clear'   => array(),
    'hooks'   => array(
      'field_create_instance'
    ),
  );

  return $info;
}

/**
 * Returns an array containing info to declare an entity_type.
 * Foreach fieldable entity type, should be declared a non fieldable entity_type.
 *
 * @return array
 *   An associative array where the keys are the entity types and whose values are :
 *   - fieldable : Whether the entity type is fieldable or not.
 *   - entity_type : (optional) The entity type.
 *   - has_revisions : (optional) Whether the entity has revisions or not.
 *   - has_translations : (optional) Whether the entity type properties can be translated.
 *   - exportable : (optional) Whether the entity type can be exported.
 *   - tables : (optional) An associative array where the keys are the tables type and the values are the tables name.
 *   - bundle_entity : (optional) The bundle entity for a fieldable entity type.
 *   - bundle_of : (optional) The bundle entity for a fieldable entity type.
 *   - module : (optional) The module managing this entity.
 *   - labels : (optional) An array containing the entity type labels.
 *     - single : (optional) The single label.
 *     - plural : (optional) The plural label.
 *   - classes : (optional) An array containing the classes required to handle the entities :
 *     - entities : (optional) The entity classes, having to provide at least "entity" as the default entity class, and additional classes foreach bundle.
 *     - controllers : (optional) The entity controllers.
 *   - callbacks : (optional) An associative array whose keys are the callback type and values are the callbacks themselves :
 *   - properties : (optional) An associative array where the keys are the property name and the values are :
 *    - type : (optional) The property type. For a list of available types @see toolbox_property_types().
 *    - reference : (optional) If the type is reference|parent, the entity type of the reference entity.
 *    - serialize : (optional) A boolean indicating if a multi value reference should be serialized rather than stored in a relation table. Will be implemented in a further version of the module.
 *    - multiple : (optional) If a reference is multi value or not.
 *    - key : (optional) The property key name.
 *    - label : (optional) The property label, often used in edit_form and views.
 *    - description : (optional) The property description, often used in edit_form and views.
 *    - has_revisions : (optional) A boolean indicating if the property should be added to the revision table.
 *    - has_translations : (optional) A boolean indicating if the property is translatable.
 *    - schemas_fields : (optional) A associative array where the keys are the schema types and the values are the matching field within that schema.
 *    - callbacks : (optional) An associative array where the keys are the callback types and the values the callbacks themselves :
 *     - getter : (optional)A custom getter for the property.
 *     - setter : (optional)A custom setter for the property.
 *     - validation : (optional)A custom validation callback for this property.
 *     - access : (optional)A custom access callback for this property.
 *     - default : (optional)A callback to return a default value when not set, arguments passed are the entity_type.
 *    - expose : (optional) An array indicating where the property should be exposed.
 *     - forms : (optional)
 *    - field : (optional) An array with the form field settings and parameters for a property.
 *   - keys : (optional) An associative array where the keys are the properties keys and the values their matching schema fields.
 *   - children inherit : (optional) An array containing the properties to be inherited by children entities.
 *   - group : (optional) The entity group.
 *
 * @see entity_toolbox_get_info().
 * @see hook_entity_toolbox_info_alter().
 * @see hook_entity_toolbox_ENTITY_TYPE_properties_update_N().
 * @see hook_entity_toolbox_entity_group_attach_info().
 * @see hook_entity_toolbox_field_category_group_info().
 * @see toolbox_property_types().
 */
function hook_entity_toolbox_info() {
  $info                 = array();
  $info['product']      = array(
    'fieldable'        => TRUE,
    'entity_type'      => 'product',
    'has_revisions'    => TRUE,
    'has_translations' => TRUE,
    'exportable'       => FALSE,
    'tables'           => array(
      'base'     => 'product',
      'revision' => 'product_revision',
      'relation' => array(
        'product_shares' => 'product_has_product_shares'
      ),
    ),
    'bundle_entity'    => 'product_type',
    'module'           => 'product',
    'labels'           => array(
      'single' => t('Product'),
      'plural' => t('Products'),
    ),
    'classes'          => array(
      'entity'        => 'Product',
      'controller'    => 'ProductController',
      'ui_controller' => 'ProductUIController',
    ),
    'properties'       => array(
      'product_id' => array(
        'type'             => 'id',
        'key'              => 'id',
        'has_revisions'    => FALSE,
        'has_translations' => FALSE,
        'expose'           => array(
          'forms' => array()
        ),
        'forms'            => array(
          'edit' => array()
        )
      ),
    ),
    'callbacks'        => array(
      'create' => '',
      'save'   => '',
      'delete' => '',
      'access' => '',
      'label'  => '',
      'uri'    => '',
    ),
    'operations'       => array(
      'add'     => TRUE,
      'delete'  => TRUE,
      'preview' => FALSE,
    ),
    'keys'             => array(
      'id' => 'product_id',
    ),
    'children_inherit' => array(
      'status',
    ),
    'group'            => 'catalog',
  );
  $info['product_type'] = array(
    'fieldable'        => FALSE,
    'entity_type'      => 'product_type',
    'has_revisions'    => FALSE,
    'has_translations' => FALSE,
    'exportable'       => TRUE,
    'tables'           => array(
      'base' => 'product_type',
    ),
    'module'           => 'product',
    'labels'           => array(
      'single' => t('Product type'),
      'plural' => t('Product types'),
    ),
    'classes'          => array(
      'entity'        => '',
      'controller'    => '',
      'ui_controller' => '',
    ),
    'properties'       => array(
      'id' => array(
        'type'                => 'id',
        'label'               => t('Product_type ID'),
        'description'         => t('The product_type ID'),
        'schemas_fields_name' => array(
          'base' => 'id'
        ),
        'schemas_fields'      => array(
          'base' => array(
            'type'        => 'int',
            'description' => 'The product_type unique identifier.',
            'serial'      => TRUE,
          )
        ),
        'callbacks'           => array(),
        'expose'              => array(
          'forms' => array()
        ),
        'forms'               => array(
          'edit' => array()
        )
      ),
    ),
    'callbacks'        => array(
      'create' => '',
      'save'   => '',
      'delete' => '',
      'access' => '',
      'label'  => '',
      'uri'    => '',
    ),
    'operations'       => array(
      'add'     => TRUE,
      'delete'  => TRUE,
      'preview' => FALSE,
    ),
    'keys'             => array(
      'id' => 'product_id',
    ),
    'children_inherit' => array(
      'status',
    ),
    'group'            => 'catalog',
  );

  return $info;
}

/**
 * Registers a hook to process and generate code for.
 *
 * @return array
 *   An associative array where the keys are the hook names and the values are :
 *   - build callback : Callback function to build the hook data.
 *   - base builder : A builder class by default.
 *   - builder argument : A key from toolbox_info to be passed as argument and get a specific builder.
 *   - builders : An associative array where the keys are the builder class and the value is the argument condition to be selected.
 */
function hook_hook_register_info() {
  $info                        = array();
  $info['entity_toolbox_info'] = array(
    'build callback' => 'entity_toolbox_info_build',
    'base builder'   => 'EntityToolboxInfoBuilder',
    'struct'         => array(
      'fieldable'        => array('type' => 'bool'),
      'entity_type'      => array('type' => 'string', 'default' => '%entity_type%'),
      'has_translations' => array('type' => 'bool'),
      'has_revisions'    => array('type' => 'bool'),
      'exportable'       => array('type' => 'bool'),
      'bundle_entity'    => array('type' => 'string', 'default' => '%entity_type%_type'),
      'bundle_of'        => array('type' => 'string', 'builder' => 'BundleOf'),
      'module'           => array('type' => 'string'),
      'labels'           => array('type' => 'array', 'builder' => 'LabelsBuilder'),
      'callbacks'        => array('type' => 'array', 'builder' => 'CallbacksBuilder'),
      'classes'          => array('type' => 'array', 'builder' => 'ClassesBuilder'),
      'properties'       => array('type' => 'array', 'builder' => 'ToolboxPropertiesBuilder'),
      'tables'           => array('type' => 'array', 'builder' => 'TablesBuilder'),
      'children_inherit' => array('type' => 'array', 'builder' => 'ChildrenInheritBuilder'),
      'group'            => array('type' => 'string'),
    ),
  );
  $info['entity_info']         = array(
    'build callback'   => 'entity_info_build',
    'base builder'     => 'EntityInfoBuilder',
    'builder argument' => 'fieldable',
    'builders'         => array(
      'EntityInfoBuilderFieldable'    => TRUE,
      'EntityInfoBuilderNotFieldable' => FALSE,
    ),
    'struct'           => array(
      'label'             => array('type' => 'string'),
      'label plural'      => array('type' => 'string'),
      'entity class'      => array('type' => 'string'),
      'controller class'  => array('type' => 'string'),
      'base table'        => array('type' => 'string'),
      'fieldable'         => array('type' => 'bool'),
      'entity keys'       => array('type' => 'array', 'builder' => 'EntityKeysBuilder'),
      'creation callback' => array('type' => 'string'),
      'access callback'   => array('type' => 'string'),
      'uri callback'      => array('type' => 'string'),
      'label callback'    => array('type' => 'string'),
      'module'            => array('type' => 'string'),
      'admin ui'          => array('type' => 'array', 'builder' => 'AdminUIBuilder'),
      'exportable'        => array('type' => 'bool'),
      'bundle_keys'       => array('type' => 'array', 'builder' => 'BundleKeysBuilder'),
    )
  );

  return $info;
}

/**
 * Declares a property type to be used by entity toolbox.
 *
 * @return array
 *   An associative array whose keys are the property type name and the values are :
 *   - default : An array to store the default values for this property type :
 *    - name :
 *    - value :
 *    - has_revisions :
 *    - has_translations :
 *    - key_name :
 *    - is_multiple :
 *    - callbacks :
 *    - drupal_property :
 *    - label :
 *    - description :
 *    - callbacks :
 *    - permissions :
 */
function hook_toolbox_property_type_info() {
  $info           = array();
  $info['id']     = array(
    'default' => array(),
  );
  $info['bundle'] = array();

  return $info;
}

/**
 * Declares widget for entity_toolbox property fields.
 * Entity toolbox widget help build the property element in an entity form.
 *
 * @return array
 *   An associative array where the keys are the widget names and the values are :
 *   - drupal type : The drupal form API matching "#type"
 *   - options :
 *   - multiple allowed :
 */
function hook_toolbox_property_widget_info() {
  $info              = array();
  $info['textfield'] = array();

  return $info;
}

/**
 * Declares a database table (schema) type for entities.
 * Used in entity_toolbox_info.
 *
 * @return array
 *   An associative array where the keys are the type name, and the values are :
 *    - name : The table name template.
 *    - description : The table description template.
 *    - build callback : The callback to build the schema.
 *
 * @see hook_entity_toolbox_entity_info().
 */
function hook_schema_type_info() {
  $info                      = array();
  $info['base']              = 'ValueSchemaBuilderBase';
  $info['revision']          = 'ValueSchemaBuilderRevision';
  $info['relation']          = 'ValueSchemaBuilderRelation';
  $info['relation_revision'] = 'ValueSchemaBuilderRelationRevision';

  return $info;
}

/**
 * Declares an entity callback type.
 * It allows to store callbacks in the toolbox_entity_info build.
 *
 * @return array
 *   An associative array whose keys are the callback type and the values are :
 *    - name : the template to build the entity type formatted callback.
 *    - default : the default callback in case the provided one during the build does not exist.
 */
function hook_toolbox_callback_type_info() {
  $info           = array();
  $info['create'] = array(
    'name'    => '%entity_type%_create',
    'default' => 'entity_toolbox_create',
  );
  $info['access'] = array(
    'name'    => '%entity_type%_access',
    'default' => 'entity_toolbox_access',
  );
  $info['uri']    = array(
    'name'    => '%entity_type%_uri',
    'default' => 'entity_toolbox_uri',
  );
  $info['page']   = array(
    'name'    => '%entity_type%_page_view',
    'default' => 'entity_toolbox_page',
  );
  $info['label']  = array(
    'name'    => '%entity_type%_label',
    'default' => 'entity_toolbox_label',
  );

  return $info;
}

/**
 * Declares a class/controller class type.
 *
 * @return array
 *   An associative array where the keys are the class types and the values are :
 *   -
 *
 */
function hook_toolbox_class_type_info() {
  $info           = array();
  $info['entity'] = array(
    'default_name' => '$upper_case_first(%entity_type%)$',
    'default_path' => '%module_path%/src/classes/entities/',
    'default_file' => '$upper_case_first(%entity_type%)$',
    'hook_info'    => 'entity_class_info',
    'group'        => 'entities'
  );

  return $info;
}

/**
 * Declares the entity class name.
 * This hook is optional. Entity Toolbox will used default parameters if not declared.
 *
 * @return array
 *   An associative array where the keys are the entity types and the values are :
 *   - class : (optional) The class name. If not specified, a default class name will be used.
 *   - path : (optional) The path of the file containing the class.
 *   - file : (optional) The file containing the class.
 */
function hook_entity_class_info() {
  $info            = array();
  $info['product'] = array(
    'class' => 'Product',
    'path'  => drupal_get_path('module', 'hedios_catalog') . '/Src/classes/entities/',
    'file'  => 'Product.inc'
  );

  return $info;
}

/**
 * Declares the entity controller class name.
 * This hook is optional. Entity Toolbox will used default parameters if not declared.
 *
 * @return array
 *   An associative array where the keys are the entity types and the values are :
 *   - class : (optional) The class name. If not specified, a default class name will be used.
 *   - path : (optional) The path of the file containing the class.
 *   - file : (optional) The file containing the class.
 */
function hook_entity_controller_info() {
  $info            = array();
  $info['product'] = array(
    'class' => 'ProductController',
    'path'  => drupal_get_path('module', 'hedios_catalog') . '/Src/classes/controllers/',
    'file'  => 'ProductController.inc'
  );

  return $info;
}

/**
 * Declares the entity ui controller class name.
 * This hook is optional. Entity Toolbox will used default parameters if not declared.
 *
 * @return array
 *   An associative array where the keys are the entity types and the values are :
 *   - class : (optional) The class name. If not specified, a default class name will be used.
 *   - path : (optional) The path of the file containing the class.
 *   - file : (optional) The file containing the class.
 */
function hook_entity_ui_controller_info() {
  $info            = array();
  $info['product'] = array(
    'class' => 'ProductUIController',
    'path'  => drupal_get_path('module', 'hedios_catalog') . '/Src/classes/controllers/',
    'file'  => 'ProductUIController.inc'
  );

  return $info;
}

/**
 * Declares the entity inline form controller class name.
 * This hook is optional. Entity Toolbox will used default parameters if not declared.
 *
 * @return array
 *   An associative array where the keys are the entity types and the values are :
 *   - class : (optional) The class name. If not specified, a default class name will be used.
 *   - path : (optional) The path of the file containing the class.
 *   - file : (optional) The file containing the class.
 */
function hook_entity_inline_form_controller_info() {
  $info            = array();
  $info['product'] = array(
    'class' => 'ProductInlineFormController',
    'path'  => drupal_get_path('module', 'hedios_catalog') . '/Src/classes/controllers/',
    'file'  => 'ProductInlineFormController.inc'
  );

  return $info;
}

/**
 * Declares an entity form type.
 * Form types are related to existing action types.
 * (Eg : "edit" form type is related to actions "add" and "edit".
 *
 * @return array
 *   An associative array where the key are the form types and the values are :
 *   - name : The form type ID template to be processed by toolbox_string_template_process().
 *   - callback : The callback to access the entity form.
 */
function hook_entity_form_type_info() {
  $info           = array();
  $info['edit']   = array(
    'name'     => '%entity_type%_edit_form',
    'callback' => 'entity_toolbox_ui_edit_form',
  );
  $info['delete'] = array(
    'name'     => '%entity_type%_delete_form',
    'callback' => 'entity_toolbox_ui_delete_form',
  );
  $info['clone']  = array(
    'name'     => '%entity_type%_clone_form',
    'callback' => 'entity_toolbox_ui_clone_form',
  );
  $info['import'] = array(
    'name'     => '%entity_type%_import_form',
    'callback' => 'entity_toolbox_ui_import_form',
  );

  return $info;
}

/**
 * Act on the system after an entity field setting has been updated.
 *
 * @param string $entity_type
 *   Then entity type.
 * @param string $bundle
 *   The bundle for which the field settings have been updated.
 * @param string $name
 *   The field name.
 *
 */
function hook_update_entity_field_settings($entity_type, $bundle, $name) {
  //Clear the cache that needs to be cleared when this hook is invoked.
  _toolbox_cache_clear('update_entity_field_settings');
}

/**
 * Declares an entity info builder.
 *
 * @return array
 *   An associative array where the keys are the builders class name and the values are :
 *    - types : An array containing the entity types whose toolbox info is processed and build by the current builder.
 */
function hook_entity_info_builder_info() {
  $info                                = array();
  $info['catalog_entity_info_builder'] = array(
    'types' => array(
      'product_category',
      'product'
    )
  );

  return $info;
}

/**
 * Acts on an entity info being process by entity toolbox.
 * This hook is invoked right before properties info are being processed.
 * Unlike "alter", this hook is here to allow other modules to add information to toolbox_info, not to alter existing data.
 *
 * @param string $entity_type
 *   The entity type.
 * @param array  $info
 *   The entity info built and processed by entity_toolbox, passed by reference.
 *
 * @see entity_toolbox_get_info().
 * @see _toolbox_info_process().
 */
function hook_toolbox_info_process($entity_type, &$info) {
  if ($entity_type == 'foobar') {
    //do whatever
  }
}

/**
 * Acts on an entity info being process by entity toolbox.
 * This hook is invoked right before properties info are being processed.
 * Unlike "alter", this hook is here to allow other modules to add information to toolbox_info, not to alter existing data.
 *
 * @param string $entity_type
 *   The entity type.
 * @param array  $info
 *   The entity info built and processed by entity_toolbox, passed by reference.
 * @param string $name
 *   The property being processed.
 *
 * @see entity_toolbox_get_info().
 * @see _toolbox_property_info_process().
 */
function hook_toolbox_property_info_process($entity_type, &$info, $name) {
  if ($entity_type == 'foobar') {
    //do whatever
  }
}

/**
 * Returns an array containing info to create an entities group.
 * Entities group are meant to ease functions use and data formatting/validation.
 *
 * @return array
 *   An associative array where the keys are the group name and whose values are :
 *   - label :
 *   - description :
 *   - entities :
 *   - classes :
 *    - group :
 *    - controller :
 *   - path :
 */
function hook_entity_group_info() {
  $info            = array();
  $info['catalog'] = array(
    'label'       => t('Catalog'),
    'description' => t('Catalog entities.'),
    'path'        => 'admin/hedios/catalog',
    'classes'     => array(
      'group'      => 'Catalog',
      'controller' => 'CatalogController'
    ),
    'entities'    => array()
  );

  return $info;
}

/**
 * Attaches one or more entity types to an entity group.
 *
 * @return array
 *   An associative array where the keys are the entity types and whose values :
 *   - group : The group to attach the entity type to.
 */
function hook_group_attach_info() {
  $info = array(
    'product_category',
    'product_family',
    'product_line',
    'product_pack',
    'product',
    'product_share'
  );

  return array_fill_keys($info, array('group' => 'catalog'));
}

/**
 * Declares a group of field categories.
 *
 * @return array
 *   An associative array where the keys are the field category groups and whose values are :
 *   - label : The field category group label.
 *   - description : A short description of the group.
 *   - entity group : The entity group to which it belongs.
 */
function hook_entity_toolbox_field_category_group_info() {
  $info                       = array();
  $info['catalog_attributes'] = array(
    'label'        => t('Catalog attribute field categories'),
    'description'  => t('A short description'),
    'entity group' => 'catalog',
  );

  return $info;
}

/**
 * Declare a field category.
 *
 * @return array
 *   An associative array where the keys are the field category names and whose values are :
 *   - label :
 *   - description :
 *   - group :
 */
function hook_entity_toolbox_field_category_info() {
  $info              = array();
  $info['technical'] = array(
    'label'       => t('Technical'),
    'description' => t('A category for technical data, such as an ISIN code, etc...'),
    'group'       => 'catalog_attributes'
  );

  return $info;
}

/**
 * Allows to alter an entity type edit form.
 *
 * @param $form
 *   The entity form, passed by reference.
 * @param $form_state
 *   The form state, passed by reference.
 * @param $entity_type
 *   The entity type.
 * @param $entity
 *   The entity.
 *
 * @see \EntityToolboxEntityController::entityEditForm()
 */
function hook_type_ENTITY_TYPE_edit_form__alter(&$form, &$form_state, $entity_type, $entity) {
  if ($entity_type == 'foobar') {
    //do whatever
  }
}

/**
 * Allows to alter an entity type delete form.
 *
 * @param $form
 *   The entity form, passed by reference.
 * @param $form_state
 *   The form state, passed by reference.
 * @param $entity_type
 *   The entity type.
 * @param $entity
 *   The entity.
 *
 * @see \EntityToolboxEntityController::entityDeleteForm()
 */
function hook_type_ENTITY_TYPE_delete_form__alter(&$form, &$form_state, $entity_type, $entity) {
  if ($entity_type == 'foobar') {
    //do whatever
  }
}

/**
 * Allows to alter an entity inline entity form.
 *
 * @param $form
 *   The entity form, passed by reference.
 * @param $form_state
 *   The form state, passed by reference.
 * @param $entity_type
 *   The entity type.
 * @param $entity
 *   The entity.
 */
function hook_type_ENTITY_TYPE_inline_entity_form__alter(&$form, &$form_state, $entity_type, $entity) {
  if ($entity_type == 'foobar') {
    //do whatever
  }
}

/**
 * Alter a property form field when attached to the entity form.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 * @param array          $form
 *   The form, passed by reference.
 * @param array          $form_state
 *   The form_state, passed by reference.
 * @param string         $langcode
 *   The language code.
 * @param string[]       $options
 *   The property fields options.
 */
function hook_property_attach_form($entity_type, $entity, $name, &$form, &$form_state, $langcode = NULL, $options = array()) {
  if ($entity_type == 'foobar') {
    //do whatever
  }
}

/**
 * Prevents drupal from loading an entity from the db if TRUE is returned.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 *
 * @return bool
 */
function hook_entity_skip_load($entity_type, $entity) {
  if ($entity_type == 'foobar') {
    return TRUE;
  }
}

/**
 * Prevents drupal from loading an entity property from the db if TRUE is returned.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 *
 * @return bool
 */
function hook_entity_property_skip_load($entity_type, $entity, $name) {
  if ($entity_type == 'foobar') {
    return TRUE;
  }
}

/**
 * Prevents drupal from loading an entity field from the db if TRUE is returned.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The field name.
 *
 * @return bool
 */
function hook_entity_field_skip_load($entity_type, $entity, $name) {
  if ($entity_type == 'foobar') {
    return TRUE;
  }
}

/**
 * Allows to alter an entity property form element before it is returned.
 *
 * @param array                   $element
 *   The element to alter, passed by reference.
 * @param string                  $entity_type
 *   The entity type.
 * @param \FieldableEntityToolbox $entity
 *   The entity for which the element was built.
 * @param string                  $name
 *   The property name.
 * @param string                  $form_id
 *   The entity form id.
 * @param null|string             $widget
 *   The field widget, or NULL if default widget was used.
 * @param array                   $options
 *   The field options.
 */
function hook_property_element_alter(&$element, $entity_type, $entity, $name, $form_id, $widget = NULL, $options = array()) {
  if (in_array($name, array_keys(entity_toolbox_get_inherited_properties($entity_type)))) {
    //do whatever
  }
}

/**
 * Allows to act on a property validation.
 * If FALSE is returned by one of the implementations, then the property "validate" is set to FALSE.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 * @param array          $form
 *   The entity form.
 * @param array          $form_state
 *   The form state, passed by reference.
 *
 * @return bool
 */
function hook_property_attach_form_validate($entity_type, $entity, $name, $form, &$form_state) {
  if (empty($entity->$name)) {
    return FALSE;
  }
}

/**
 * Allows to act on a property validation.
 * If FALSE is returned by one of the implementations, then the property is set to error.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 * @param mixed          $value
 *   The property value to validate.
 *
 * @return bool
 */
function hook_property_validate($entity_type, $entity, $name, $value) {
  if (empty($entity->$name)) {
    return FALSE;
  }
}