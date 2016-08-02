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
 * The module is based on two main concepts :
 * - Entities groups
 * - Heritage
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
 * Declares a property type to be used by entity toolbox.
 *
 * @return array
 *   An associative array whose keys are the property type name and the values are :
 *   - description : A short description about the property type.
 *   - default_description : (optional) A default description template.
 *   - drupal_property : The data type as allowed by drupal.
 *   - drupal_property_callback : (optional) If "drupal_property" is unset, a callback to return the drupal property data type.
 *     To be used for reference and parent properties.
 *   - default_value : (optional) The default value when the entity property value is empty and none was set in hook_entity_toolbox_entity_info().
 *   - default_is_unique : (optional) A boolean indicating if the property should be unique.
 *   - default_key : (optional) The default key name.
 *   - default_schema : An array used to build the property schema field.
 *   - default_widget : (optional) The property type default widget.
 *   - default_views_expose : (optional) An array to indicate if the property type is by default exposed in views.
 *   - default_forms_expose : (optional) An array to indicate if the property type is by default exposed in the entities form types (edit, delete, clone, etc...)
 *   - default_has_revisions : (optional) A boolean indicating if the property type has by default revisions.
 *   - default_has_translations : (optional) A boolean indicating if the property type is by default translatable.
 *   - default_multiple : (optional) A boolean indicating if the property type is by default multi value.
 *   - default_callbacks : (optional) An array of default callbacks to be passed to hook_entity_property_info() & hook_entity_property_info_alter().
 *   - default_permissions : (optional) An array of permissions to be passed to hook_entity_property_info() & hook_entity_property_info_alter().
 *   - default_views_handlers : (optional) A callable function to retrieve the property type default views handlers.
 */
function hook_toolbox_property_type_info() {
  $info           = array();
  $info['id']     = array(
	'description'              => 'An entity unique identifier property.',
	'drupal_property'          => 'decimal',
	'default_label'            => '%entity_type% ID',
	'default_description'      => 'The %entity_type% ID.',
	'default_value'            => 0,
	'default_is_unique'        => TRUE,
	'default_key'              => 'id',
	'default_schema'           => array(
	  'base' => array(
		'type'     => 'int',
		'not null' => TRUE,
		'unsigned' => TRUE,
		'default'  => 0,
	  )
	),
	'default_schemas_fields'   => array(
	  'base'     => '%entity_type%_id',
	  'revision' => '%entity_type%_id',
	),
	'default_views_expose'     => array(),
	'default_forms_expose'     => array(
	  'edit' => FALSE
	),
	'default_required'         => array(),
	'default_has_revisions'    => FALSE,
	'default_has_translations' => FALSE,
	'default_multiple'         => FALSE,
	'default_views_handlers'   => 'toolbox_numeric_property_default_views_handlers'
  );
  $info['bundle'] = array(
	'description'              => 'A entity bundle.',
	'drupal_property'          => 'text',
	'default_description'      => 'The %entity_type% type.',
	'default_value'            => '',
	'default_key'              => 'bundle',
	'default_schema'           => array(
	  'type'     => 'varchar',
	  'length'   => 255,
	  'not null' => TRUE,
	  'default'  => ''
	),
	'default_schemas_fields'   => array(
	  'base' => 'type',
	),
	'default_views_expose'     => array(),
	'default_forms_expose'     => array(
	  'edit' => FALSE
	),
	'default_has_revisions'    => FALSE,
	'default_has_translations' => FALSE,
	'default_multiple'         => FALSE,
	'default_callbacks'        => array(),
	'default_permissions'      => array(),
	'default_views_handlers'   => 'toolbox_string_property_default_views_handlers'
  );

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
  $info                 = array();
  $info['textfield']    = array(
	'drupal type'      => 'textfield',
	'options'          => array(),
	'multiple allowed' => TRUE,
  );
  $info['text']         = array(
	'drupal type'      => 'textarea',
	'options'          => array(),
	'multiple allowed' => TRUE,
  );
  $info['date']         = array();
  $info['select']       = array();
  $info['checkbox']     = array();
  $info['radio']        = array();
  $info['autocomplete'] = array();

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
  $info['base']              = array(
	'name'           => '%entity_type%',
	'description'    => 'The base table for %entity_type% entities.',
	'build callback' => 'base_schema_build',
  );
  $info['revision']          = array(
	'name'           => '%entity_type%_revision',
	'description'    => 'Keeps track of %entity_type% revisions.',
	'build callback' => 'revision_schema_build',
  );
  $info['relation']          = array(
	'name'           => '%entity_type%_has_%relation_type%',
	'description'    => 'A relation table between %entity_type% and %relation_type%.',
	'build callback' => 'relation_schema_build',
  );
  $info['relation_revision'] = array(
	'name'           => '%entity_type%_has_%relation_type%_revision',
	'description'    => 'Keeps track of %relation_type% relation revisions.',
	'build callback' => 'relation_revision_schema_build',
  );

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
 * Declares an action type, to act on an entity.
 * Action info is used by EntityToolboxUIController to build menu items.
 *
 * @return array
 *   An associative array where the keys are the action type name and the values are :
 *   - title : The title of the action, used both for menu links and buttons.
 *   - path item : The isolated path item for this action.
 *   - path : The path model for this action.
 */
function hook_toolbox_action_type_info() {
  $info        = array();
  $info['add'] = array(
	'title'     => 'Add %entity_type%',
	'path item' => 'add',
	'path'      => '%entity_path%/add/%wildcard%'
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
 * Returns an array containing info to declare an entity_type.
 * Foreach fieldable entity type, should be declared a non fieldable entity_type.
 *
 * @return array
 *   An associative array where the keys are the entity types and whose values are :
 *   - entity_type : The entity type.
 *   - base table : (optional) The base table for this entity type.
 *   - revision table : (optional) The table to store revisions.
 *   - has_revisions : Whether the entity type has revisions or not.
 *   - has_translations : Whether the entity type properties can be translated.
 *   - fieldable : Whether the entity type is fieldable or not.
 *   - exportable : Whether the entity type can be exported.
 *    - defaults : FALSE if entity is fieldable, TRUE if entity is not fieldable.
 *   - tables : (optional) An array of the tables required by the entity type, at the exception of "base table" and "revision table".
 *   - bundle_entity : (optional) The bundle entity for a fieldable entity type.
 *   - module : The module managing this entity.
 *   - paths : An array of paths used to manage the entities :
 *     - root : The root path of an entity type.
 *     - admin : The relative path to administer the entities.
 *     - manage : The relative path to edit an entity.
 *   - labels : (optional) An array containing the entity type labels.
 *     - single : The single label.
 *     - plural : The plural label.
 *   - classes : An array containing the classes required to handle the entities :
 *     - entities : The entity classes, having to provide at least "entity" as the default entity class, and additional classes foreach bundle.
 *     - controllers : The entity controllers.
 *   - callbacks : (optional) An associative array whose keys are the callback type and values are the callbacks themselves :
 *    - create : The entity creation callback.
 *    - access : The entity access callback.
 *    - uri : The entity uri callback.
 *    - label : The entity title callback.
 *    - page : The entity page view callback.
 *   - properties : An associative array where the keys are the property name and the values are :
 *    - type : The property type. For a list of available types @see toolbox_property_types().
 *    - reference : (optional) If the type is reference|parent, the entity type of the reference entity.
 *    - serialize : (optional) A boolean indicating if a multi value reference should be serialized rather than stored in a relation table. Will be implemented in a further version of the module.
 *    - multiple : (optional) If a reference is multi value or not.
 *    - limit : (optional) The number of values allowed when multi value.
 *    - key : The property key.
 *    - label : The property label, often used in edit_form and views.
 *    - description : The property description, often used in edit_form and views.
 *    - required :
 *    - has_revisions : (optional) A boolean indicating if the property should be added to the revision table.
 *    - has_translations : (optional) A boolean indicating if the property is translatable.
 *    - schemas : (optional) An associative array where the keys are schema types and the values are the matching schemas names.
 *    - schemas_fields : (optional) A associative array where the keys are the schema types and the values are the matching field within that schema.
 * @see hook_schema_type_info().
 *    - callbacks : (optional) An associative array where the keys are the callback types and the values the callbacks themselves :
 *     - getter : A custom getter for the property.
 *     - setter : A custom setter for the property.
 *     - validation : A custom validation callback for this property.
 *     - access : A custom access callback for this property.
 *     - default : A callback to return a default value when not set, arguments passed are the entity_type.
 *    - permissions : (optional)
 *    - expose : (optional) An array indicating where the property should be exposed.
 *     - forms : (optional)
 *     - views : A boolean indicating if a property should be exposed to the admin view.
 *    - field : (optional) An array with the form field settings and parameters for a property.
 *     - widget : (optional) The default widget to access the property in a form.
 *     - multiple : (optional) A boolean indicating if the fields accepts multiple values.
 *   - keys : (optional) An associative array where the keys are the properties keys and the values their matching schema fields.
 *   - children inherit : (optional) An array whose values are the properties to be inherited by children entities.
 *   - group : (optional) The entity group.
 *
 * @see entity_toolbox_entity_get_info().
 * @see hook_entity_toolbox_entity_info_alter().
 * @see hook_entity_toolbox_ENTITY_TYPE_properties_update_N().
 * @see hook_entity_toolbox_entity_group_attach_info().
 * @see hook_entity_toolbox_field_category_group_info().
 * @see toolbox_property_types().
 */
function hook_entity_toolbox_entity_info() {
  $info            = array();
  $info['product'] = array(
	'entity_type'      => 'product',
	'base table'       => 'product',
	'revision table'   => 'product_revision',
	'has_revisions'    => TRUE,
	'has_translations' => TRUE,
	'fieldable'        => TRUE,
	'bundle_entity'    => 'product_type',
	'module'           => 'hedios_catalog',
	'exportable'       => FALSE,
	'paths'            => array(
	  'root'   => 'admin/hedios/catalog',
	  'admin'  => 'products',
	  'manage' => 'edit'
	),
	//Stores processed labels.
	'labels'           => array(
	  'single' => entity_type2entity_label('product'),
	  'plural' => entity_type2entity_label_plural('product')
	),
	//Stores processed classes.
	'classes'          => array(
	  'controllers' => array(
		'controller' => '',
		'ui'         => ''
	  ),
	  'entities'    => array(
		'entity' => '',
	  ),
	),
	//Stores processed callbacks.
	'callbacks'        => array(
	  'create' => 'product_create',
	  'access' => 'product_access',
	  'uri'    => 'product_uri',
	  'label'  => 'product_label',
	  'title'  => 'product_title',
	  'page'   => 'product_page_view'
	),
	//Properties
	'properties'       => array(
	  'product_id'     => array(
		'type'             => 'id',
		'label'            => 'Product ID',
		'description'      => 'The product ID.',
		'required'         => array(
		  'create' => FALSE,
		  'edit'   => TRUE,
		),
		'has_revisions'    => FALSE,
		'has_translations' => FALSE,
		'schemas'          => array(
		  'base'     => array(),
		  'revision' => array(
			'description' => 'Revision de mon id.'
		  ),
		),
		'schemas_fields'   => array(
		  'base'     => 'product_id',
		  'revision' => 'product_id'
		),
		'callbacks'        => array(),
		'permissions'      => array(),
		'expose'           => array(
		  'views' => TRUE,
		  'forms' => array(),
		),
		'default'          => '',
	  ),
	  'type'           => array(
		'type'             => 'bundle',
		'label'            => 'Bundle',
		'description'      => 'The product_type.',
		'required'         => array(
		  'create' => FALSE,
		  'edit'   => TRUE,
		),
		'has_revisions'    => FALSE,
		'has_translations' => FALSE,
		'schemas'          => array(),
		'schemas_fields'   => array(
		  'product' => 'type',
		),
		'callbacks'        => array(),
		'permissions'      => array(),
		'expose'           => array(
		  'views' => TRUE,
		  'forms' => array(),
		),
		'default'          => '',
	  ),
	  'product_family' => array(
		'type'             => 'parent',
		'reference'        => 'product_family',
		'multiple'         => FALSE,
		'label'            => 'Product family',
		'description'      => 'The parent product family.',
		'required'         => array(
		  'create' => FALSE,
		  'edit'   => TRUE,
		),
		'has_revisions'    => TRUE,
		'has_translations' => FALSE,
		'schemas'          => array(
		  'product' => array()
		),
		'schemas_fields'   => array(
		  'product'          => 'product_family_id',
		  'product_revision' => 'product_family_id'
		),
		'callbacks'        => array(
		  'getter'              => '',
		  'setter'              => '',
		  'validation callback' => '',
		  'access callback'     => '',
		),
		'permissions'      => array(
		  'getter' => 'custom_getter_permission',
		  'setter' => 'custom_setter_permission',
		  'access' => 'custom_access_permission',
		),
		'expose'           => array(
		  'views' => TRUE,
		  'forms' => array(),
		),
		'default'          => 0,
	  ),
	  'author'         => array(
		'type'             => 'reference',
		'reference'        => 'user',
		'key'              => 'uid',
		'multiple'         => FALSE,
		'label'            => 'Author',
		'description'      => 'The product author.',
		'required'         => array(
		  'create' => FALSE,
		  'edit'   => TRUE,
		),
		'has_revisions'    => TRUE,
		'has_translations' => FALSE,
		'schemas'          => array(
		  'product' => array()
		),
		'schemas_fields'   => array(
		  'product'          => 'uid',
		  'product_revision' => 'uid'
		),
		'callbacks'        => array(
		  'default' => 'user_id',
		),
		'permissions'      => array(),
		'expose'           => array(
		  'views' => TRUE,
		  'forms' => array(),
		),
	  ),
	),
	'keys'             => array(
	  'id'     => 'product_id',
	  'bundle' => 'type',
	),
	'children inherit' => array(
	  'product_family',
	),
	'group'            => 'catalog',
	'operations'       => array(
	  'add'    => array(
		''
	  ),
	  'view'   => array(),
	  'delete' => array(),
	)
  );

  return $info;
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
 * Provides information on where to find the object resources, such as controllers, templates, etc...
 *
 * @return array
 *   An associative array where the keys are the resource types and the values are :
 *    - classes : An associative array where the keys are the classes types :
 *     - controllers : An associative array where the keys are the controllers class names and the values are :
 *       - class : The entity controller class.
 *       - path : The path to access the class.
 *     - entities : An associative array where the keys are the entity class names and the values are :
 *       - class : The entity controller class.
 *       - path : The path to access the class.
 *    - templates :
 */
function hook_entity_resources_info() {
  $info            = array();
  $info['product'] = array(
	'classes'   => array(
	  'controllers' => array(
		'controller'    => array(
		  'name' => 'ProductController.inc',
		  'path' => ENTITY_TOOLBOX_PATH . '/Src/classes/controllers/'
		),
		'ui controller' => array(
		  'name' => '',
		  'path' => ENTITY_TOOLBOX_PATH . '/Src/classes/controllers'
		)
	  ),
	  'entities'    => array(
		'entity' => array(
		  'name' => 'Product.inc',
		  'path' => ENTITY_TOOLBOX_PATH . 'Src/classes/entities'
		),
	  ),
	),
	'templates' => array(
	  'page' => array(
		'name' => 'product.tpl.php',
		'path' => ENTITY_TOOLBOX_PATH . 'templates/entities/page'
	  )
	),
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
 * @see entity_toolbox_entity_get_info().
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
 * @see entity_toolbox_entity_get_info().
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
function hook_entity_group_attach_info() {
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
 * @param string               $entity_type
 *   The entity type.
 * @param \EntityToolboxEntity $entity
 *   The entity.
 * @param string               $name
 *   The property name.
 * @param array                $form
 *   The form, passed by reference.
 * @param array                $form_state
 *   The form_state, passed by reference.
 * @param string               $langcode
 *   The language code.
 * @param string[]             $options
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
 * @param string               $entity_type
 *   The entity type.
 * @param \EntityToolboxEntity $entity
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
 * @param string               $entity_type
 *   The entity type.
 * @param \EntityToolboxEntity $entity
 *   The entity.
 * @param string               $name
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
 * @param string               $entity_type
 *   The entity type.
 * @param \EntityToolboxEntity $entity
 *   The entity.
 * @param string               $name
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
 * @param array                         $element
 *   The element to alter, passed by reference.
 * @param string                        $entity_type
 *   The entity type.
 * @param \EntityToolboxFieldableEntity $entity
 *   The entity for which the element was built.
 * @param string                        $name
 *   The property name.
 * @param string                        $form_id
 *   The entity form id.
 * @param null|string                   $widget
 *   The field widget, or NULL if default widget was used.
 * @param array                         $options
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
 * @param string               $entity_type
 *   The entity type.
 * @param \EntityToolboxEntity $entity
 *   The entity.
 * @param string               $name
 *   The property name.
 * @param array                $form
 *   The entity form.
 * @param array                $form_state
 *   The form state, passed by reference.
 *
 * @return bool
 */
function hooh_property_attach_form_validate($entity_type, $entity, $name, $form, &$form_state) {
  if (empty($entity->$name)) {
	return FALSE;
  }
}

/**
 * Allows to act on a property validation.
 * If FALSE is returned by one of the implementations, then the property is set to error.
 *
 * @param string               $entity_type
 *   The entity type.
 * @param \EntityToolboxEntity $entity
 *   The entity.
 * @param string               $name
 *   The property name.
 * @param mixed                $value
 *   The property value to validate.
 *
 * @return bool
 */
function hook_property_validate($entity_type, $entity, $name, $value) {
  if (empty($entity->$name)) {
	return FALSE;
  }
}