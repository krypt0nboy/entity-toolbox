<?php

/**
 * Class EntityToolboxInfoPropertyModel
 */
class EntityToolboxInfoPropertyModel extends EntityToolboxInfoRecursiveModel {
  /**
   * @access protected
   * @var string $propertyType
   *   The property type.
   *
   * @see hook_toolbox_property_type_info().
   */
  protected $propertyType;
  /**
   * @access protected
   * @var array $propertyTypeInfo
   *   The property type info.
   *
   * @see entity_toolbox_property_type_get_info().
   */
  protected $propertyTypeInfo = array();

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'parent_key' => 'properties',
        'structure'  => array(
          'type'                  => array(
            'type'    => 'string',
            'method'  => 'buildType',
            'default' => '%property_default_type%',
          ),
          'php type'              => array(
            'type'    => 'string',
            'method'  => 'buildPhpType',
            'default' => '%property_default_php_type%',
          ),
          'drupal type'           => array(
            'type'    => 'string',
            'method'  => 'buildDrupalType',
            'default' => '%property_default_drupal_type%',
          ),
          'reference'             => array(
            'type'     => 'string',
            'default'  => '%property_default_reference%',
            'unset if' => 'is_null:c:'
          ),
          'label'                 => array(
            'type'    => 'string',
            'default' => '%property_default_label%',
          ),
          'description'           => array(
            'type'    => 'string',
            'default' => '%property_default_description%',
          ),
          'multiple'              => array(
            'type'    => 'boolean',
            'method'  => 'buildMultiple',
            'default' => '%property_default_multiple%',
          ),
          'has_revisions'         => array(
            'type'    => 'boolean',
            'method'  => 'buildHasRevisions',
            'default' => '%property_default_has_revisions%',
          ),
          'has_translations'      => array(
            'type'    => 'boolean',
            'method'  => 'buildHasTranslations',
            'default' => '%property_default_has_translations%',
          ),
          'required'              => array(
            'type'    => 'boolean',
            'method'  => 'buildRequired',
            'default' => '%property_default_required%',
          ),
          'serialize'             => array(
            'type'    => 'boolean',
            'default' => '%property_default_serialize%',
          ),
          'key'                   => array(
            'type'    => 'string',
            'method'  => 'buildPropertyKey',
            'default' => '%property_default_key%',
          ),
          'tables'                => array(
            'type'   => 'array',
            'method' => 'buildTables',
          ),
          'schemas_fields_name'   => array(
            'type'   => 'array',
            'method' => 'buildSchemasFieldsName',
          ),
          'schemas_fields'        => array(
            'type'   => 'array',
            'method' => 'buildSchemasFields',
          ),
          'forms'                 => array(
            'type'   => 'array',
            'method' => 'buildForms',
          ),
          'callbacks'             => array(
            'type'   => 'array',
            'method' => 'buildCallbacks',
          ),
          'is_unique'             => array(
            'type'    => 'boolean',
            'method'  => 'buildIsUnique',
            'default' => '%property_default_is_unique%',
          ),
          'views expose'          => array(
            'type'    => 'boolean',
            'method'  => 'buildViewsExpose',
            'default' => '%property_default_views_expose%',
          ),
          'value'                 => array(
            'type'   => 'array',
            'method' => 'buildValue',
            'model'  => 'entity_toolbox_info_property_value'
          ),
          'children_inherit'      => array(
            'type'    => 'boolean',
            'default' => '%property_default_children_inherit%',
          ),
          'weight'                => array(
            'type'    => 'int',
            'method'  => 'buildWeight',
            'default' => '%property_default_weight%',
          ),
          'self_numeric_property' => array(
            'type'     => 'array',
            'method'   => 'buildSelfNumericProperty',
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }

  /**
   * @return string
   */
  public function getPropertyType() {
    return $this->propertyType;
  }

  /**
   * @param string $propertyType
   */
  public function setPropertyType($propertyType) {
    $this->propertyType = $propertyType;
  }

  /**
   * @return array
   */
  public function getPropertyTypeInfo() {
    return $this->propertyTypeInfo;
  }

  /**
   * @param array $propertyTypeInfo
   */
  public function setPropertyTypeInfo($propertyTypeInfo) {
    $this->propertyTypeInfo = $propertyTypeInfo;
  }
}