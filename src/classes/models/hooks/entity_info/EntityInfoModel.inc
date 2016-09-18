<?php

/**
 * Class EntityInfoModel
 */
class EntityInfoModel extends HookModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'label'             => array(
            'type'    => 'string',
            'default' => '%toolbox_info_labels_single%',
          ),
          'plural label'      => array(
            'type'    => 'string',
            'default' => '%toolbox_info_labels_plural%',
          ),
          'entity class'      => array(
            'type'    => 'string',
            'default' => '%toolbox_info_classes_entity_class%',
          ),
          'controller class'  => array(
            'type'    => 'string',
            'default' => '%toolbox_info_classes_controller_class%',
          ),
          'base table'        => array(
            'type'    => 'string',
            'default' => '%toolbox_info_tables_base%',
          ),
          'revision table'    => array(
            'type'     => 'string',
            'default'  => '%toolbox_info_tables_revision%',
            'unset if' => 'is_null:c:'
          ),
          'fieldable'         => array(
            'type'    => 'boolean',
            'default' => '%toolbox_info_fieldable%',
          ),
          'entity keys'       => array(
            'type'   => 'array',
            'method' => 'buildEntityKeys',
          ),
//          'operations ui'     => array(
//            'type'   => 'array',
//            'method' => 'buildOperationsUi',
//          ),
          'label callback'    => array(
            'type'    => 'string',
            'default' => '%toolbox_info_callbacks_label%',
          ),
          'uri callback'      => array(
            'type'    => 'string',
            'default' => '%toolbox_info_callbacks_uri%',
          ),
          'creation callback' => array(
            'type'    => 'string',
            'default' => '%toolbox_info_callbacks_create%',
          ),
          'access callback'   => array(
            'type'    => 'string',
            'default' => '%toolbox_info_callbacks_access%',
          ),
          'module'            => array(
            'type'    => 'string',
            'default' => '%toolbox_info_module%',
          ),
//          'admin ui'          => array(
//            'type'   => 'array',
//            'method' => 'buildAdminUi',
//            'model'  => 'entity_info_admin_ui'
//          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}