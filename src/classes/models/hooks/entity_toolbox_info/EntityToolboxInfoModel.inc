<?php

/**
 * Class EntityToolboxInfoModel
 */
class EntityToolboxInfoModel extends HookModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'hook'      => 'entity_toolbox_info',
        'structure' => array(
          'entity_type'      => array(
            'type'    => 'string',
            'default' => '%toolbox_info_entity_type%',
          ),
          'fieldable'        => array(
            'type'    => 'boolean',
            'default' => '%toolbox_info_fieldable%',
          ),
          'group'            => array(
            'type'    => 'string',
            'default' => '%toolbox_info_group%',
          ),
          'has_revisions'    => array(
            'type'    => 'boolean',
            'method'  => '',
            'default' => '',
            'model'   => ''
          ),
          'has_translations' => array(
            'type'    => 'boolean',
            'method'  => '',
            'default' => '',
            'model'   => ''
          ),
          'exportable'       => array(
            'type'    => 'boolean',
            'method'  => '',
            'default' => '',
            'model'   => ''
          ),
          'module'           => array(
            'type'    => 'string',
            'method'  => '',
            'default' => '%toolbox_info_module%',
            'model'   => ''
          ),
          'labels'           => array(
            'type'    => 'array',
            'method'  => 'buildLabels',
            'model'   => 'entity_toolbox_labels'
          ),
          'root path'        => array(
            'type'    => 'string',
            'method'  => 'buildRootPath',
          ),
          'classes'          => array(
            'type'    => 'array',
            'method'  => 'buildClasses',
            'default' => '',
            'model'   => 'entity_toolbox_classes'
          ),
          'properties'       => array(
            'type'    => 'array',
            'method'  => 'buildProperties',
            'default' => '',
            'model'   => 'entity_toolbox_properties'
          ),
          'tables'           => array(
            'type'    => 'array',
            'method'  => 'buildTables',
            'default' => '',
            'model'   => 'entity_toolbox_info_tables'
          ),
          'callbacks'        => array(
            'type'    => 'array',
            'method'  => 'buildCallbacks',
            'default' => '',
            'model'   => ''
          ),
          'operations'       => array(
            'type'    => 'array',
            'method'  => 'buildOperations',
            'default' => '',
            'model'   => 'entity_toolbox_operations'
          ),
          'keys'             => array(
            'type'    => 'array',
            'method'  => 'buildKeys',
            'default' => '',
            'model'   => ''
          ),
          'children_inherit' => array(
            'type'    => 'array',
            'method'  => 'buildChildrenInherit',
            'default' => '',
            'model'   => ''
          ),
        )
      ), $args
    );
    parent::__construct($args);
  }
}